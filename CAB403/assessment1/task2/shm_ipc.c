#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "operations.h"

// References:
// *   https://man7.org/training/download/ipc_prog_pshm_slides.pdf
// *   CAB403 Topic 4 lecture notes and practical.

// Compile with flags: -lrt -lpthread

/**
 * Friendly names for supported worker process operations.
 */
char* op_names[] = {
    "add", "sub", "mul", "div", "quit"
};

/**
 * Controller: initialise a shared_object_t, creating a block of shared memory
 * with the designated name, and setting its storage capacity to the size of a
 * shared data block.
 *
 * PRE: n/a
 *
 * POST: shm_unlink has been invoked to delete any previous instance of the
 *       shared memory object, if it exists.
 * AND   The share name has been saved in shm->name.
 * AND   shm_open has been invoked to obtain a file descriptor connected to a
 *       newly created shared memory object with size equal to the size of a
 *       shared_data_t struct, with support for read and write operations. The
 *       file descriptor should be saved in shm->fd, regardless of the final outcome.
 * AND   ftruncate has been invoked to set the size of the shared memory object
 *       equal to the size of a shared_data_t struct.
 * AND   mmap has been invoked to obtain a pointer to the shared memory, and the
 *       result has been stored in shm->data, regardless of the final outcome.
 * AND   (this code is provided for you, don't interfere with it) The shared
 *       semaphore has been initialised to manage access to the shared buffer.
 * AND   Semaphores have been initialised in a waiting state.
 *
 * \param shm The address of a shared memory control structure which will be
 *            populated by this function.
 * \param share_name The unique string used to identify the shared memory object.
 * \returns Returns true if and only if shm->fd >= 0 and shm->data != MAP_FAILED.
 *          Even if false is returned, shm->fd should contain the value returned
 *          by shm_open, and shm->data should contain the value returned by mmap.
 */
bool create_shared_object( shared_memory_t* shm, const char* share_name ) {
    // Remove any previous instance of the shared memory object, if it exists.
    if (shm != NULL) shm_unlink(share_name);

    // Assign share name to shm->name.
    shm->name = share_name;

    // Create the shared memory object, allowing read-write access, and saving the
    // resulting file descriptor in shm->fd. If creation failed, ensure
    // that shm->data is NULL and return false.

    shm->fd = shm_open(shm->name, O_CREAT | O_RDWR, 438);
    if (shm->fd == -1) {
        shm->data = NULL;
        return false;
    }

    // Set the capacity of the shared memory object via ftruncate. If the
    // operation fails, ensure that shm->data is NULL and return false.
    if (ftruncate(shm->fd, sizeof(shared_data_t)) == -1) {
        shm->data = NULL;
        return false;
    }

    // Otherwise, attempt to map the shared memory via mmap, and save the address
    // in shm->data. If mapping fails, return false.
    shm->data = mmap(0, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm->fd, 0);
    if (shm->data == MAP_FAILED) return false;

    // Do not alter the following semaphore initialisation code.
    sem_init( &shm->data->controller_semaphore, 1, 0 );
    sem_init( &shm->data->worker_semaphore, 1, 0 );

    // If we reach this point we should return true.
    return true;
}

/**
 * Controller: destroys the shared memory object managed by a shared memory
 * control block.
 *
 * PRE: create_shared_object( shm, shm->name ) has previously been
 *      successfully invoked.
 *
 * POST: munmap has been invoked to remove the mapped memory from the address
 *       space
 * AND   shm_unlink has been invoked to remove the object
 * AND   shm->fd == -1
 * AND   shm->data == NULL.
 *
 * \param shm The address of a shared memory control block.
 */
void destroy_shared_object( shared_memory_t* shm ) {
    // Remove the shared memory object.
    munmap(shm->data, sizeof(shared_data_t));
    shm_unlink(shm->name);
    shm->fd = -1;
    shm->data = NULL;
}

/**
 * Controller: Uses shared memory to request and wait for work to be completed
 * by worker process.
 *
 * PRE: create_shared_memory(shm, ...) has previously been invoked, and returned
 *      true.
 *
 * POST: shm->data->operation == op
 * AND   shm->data->lhs == lhs
 * AND   shm->data->rhs == rhs
 * AND   shm->data->result == whatever value the worker has placed there.
 *
 * \param shm The address of a shared memory control block.
 * \param op  The operation code which tells the worker what operation to carry
 *            out.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return Returns the value of shm->data->result, which will be furnished by
 *         the worker. (The worker may not know the proper rules of arithmetic.
 *         We accept whatever the worker gives us.)
 */
double request_work( shared_memory_t* shm, operation_t op, double lhs, double rhs ) {
    // Copy the supplied values of op, lhs and rhs into the corresponding fields
    // of the shared data object.
    shm->data->operation = op;
    shm->data->lhs = lhs;
    shm->data->rhs = rhs;


    // Do not alter the following semaphore code. It sends the request to the
    // worker, and waits for the response in a reliable manner.
    sem_post( &shm->data->controller_semaphore );
    sem_wait( &shm->data->worker_semaphore );

    // Modify the following line to make the function return the result computed
    // by the worker process. This will be stored in the result field of the
    // shared data object.
    return shm->data->result;
}

/**
 * Worker: Get a file descriptor which may be used to interact with a shared memory
 * object, and map the shared object to get its address.
 *
 * PRE: The Controller has previously invoked create_shared_fd to instantiate the
 *      shared memory object.
 *
 * POST: shm_open has been invoked to obtain a file descriptor connected to a
 *       shared_data_t struct, with support for read and write operations. The
 *       file descriptor should be saved in shm->fd, regardless of the final outcome.
 * AND   mmap has been invoked to obtain a pointer to the shared memory, and the
 *       result has been stored in shm->data, regardless of the final outcome.
 *
 * \param share_name The unique identification string of the shared memory object.
 * \return Returns true if and only if shm->fd >= 0 and
 *         shm->data != NULL.
 */
bool get_shared_object( shared_memory_t* shm, const char* share_name ) {
    // Get a file descriptor connected to shared memory object and save in
    // shm->fd. If the operation fails, ensure that shm->data is
    // NULL and return false.
    shm->fd = shm_open(share_name, O_RDWR, 438);
    if (shm->fd == -1) {
        shm->data = NULL;
        return false;
    }
    // Otherwise, attempt to map the shared memory via mmap, and save the address
    // in shm->data. If mapping fails, return false.
    shm->data = mmap(0, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm->fd, 0);
    if (shm->data == MAP_FAILED) return false;
    // Modify the remaining stub only if necessary.
    return true;
}

/**
 * Worker: wait for work request, then complete the required action and notify
 * the controller that the action is complete.
 *
 * PRE: get_shared_object(shm, ... ) has been successfully invoked.
 *
 * POST: sem_wait has been invoked to pause execution until work is available.
 * AND   IF shm->data->operation is op_quit
 *       THEN
 *           munmap has been invoked to remove the shared data object from the
 *           address space,
 *           AND shm->fd == -1
 *           AND shm->data == NULL
 *           AND returned value will be false.
 *       OTHERWISE
 *          The arithmetic operation corresponding to shm->data->operation
 *          has been performed, and the resulting value has been assigned to
 *          shm->data->result. Other shared data fields are preserved as-is.
 * AND   sem_post has been invoked to notify the controller that the request has
 *       been processed.
 *
 * \param shm The address of a shared memory control structure.
 * \return Returns true if and only if the operation is no op_quit.
 */
bool do_work( shared_memory_t* shm ) {
    bool retVal = true;

    // Do not alter the following instruction, which waits for work
    sem_wait( &shm->data->controller_semaphore );

    // Update the value of local variable retVal and/or shm->data->result
    // as required.

    switch (shm->data->operation) {
        case op_add:
            shm->data->result = shm->data->lhs + shm->data->rhs;
            break;
        case op_sub:
            shm->data->result = shm->data->lhs - shm->data->rhs;
            break;
        case op_mul:
            shm->data->result = shm->data->lhs * shm->data->rhs;
            break;
        case op_div:
            shm->data->result = shm->data->lhs / shm->data->rhs;
            break;
        case op_quit:
        default:
            retVal = false;
            break;
    }

    // Do not alter the following instruction which send the result back to the
    // controller.
    sem_post( &shm->data->worker_semaphore );

    // If retval is false, the memory needs to be unmapped, but that must be
    // done _after_ posting the semaphore. Un-map the shared data, and assign
    // values to shm->data and shm-fd as noted above.

    if (!retVal) {
        munmap(shm->data, sizeof(shared_data_t));
        shm->fd = -1;
        shm->data = NULL;
    }

    // Keep this line to return the result.
    return retVal;
}

double next_rand() {
    return 100.0 * rand() / RAND_MAX;
}

operation_t next_op() {
    return (operation_t)(rand() % op_quit);
}

#define SHARE_NAME "/xyzzy_123"

void controller_main() {
    srand( 42 );
    printf( "Controller starting.\n" );

    shared_memory_t shm;

    if ( create_shared_object( &shm, SHARE_NAME ) ) {
        for ( int i = 0; i < 20; i++ ) {
            operation_t op = next_op();
            double lhs = next_rand();
            double rhs = next_rand();
            double result = request_work( &shm, op, lhs, rhs );
            printf( "%s(%0.2f, %0.2f) = %0.2f\n", op_names[op], lhs, rhs, result );
        }

        request_work( &shm, op_quit, 0, 0 );
        printf( "Controller finished.\n" );

        destroy_shared_object( &shm );
    }
    else {
        printf( "Shared memory creation failed.\n" );
    }
}

void worker_main() {
    printf( "Worker starting.\n" );

    shared_memory_t shm;

    if ( get_shared_object( &shm, SHARE_NAME ) ) {
        while ( do_work( &shm ) ) {}

        printf( "Worker has been told to quit.\n" );
    }
    else {
        printf( "Shared memory connection failed.\n" );
    }
}

int main(void ) {
    pid_t childPid = -1;
    // Invoke the fork function to spawn the worker process, and save the result
    // as childPid.
    childPid = fork();

    if ( childPid < 0 ) { /* error occurred */
        fprintf( stderr, "Fork failed\n" );
        return 1;
    }
    else if ( childPid == 0 ) {
        // Sleep 1 second to give the controller time to create the shared memory
        // object, then invoke worker_main.
        sleep( 1 );
        worker_main();
    }
    else { /* parent process */
        // Invoke controller_main.
        controller_main();
    }

    return 0;
}