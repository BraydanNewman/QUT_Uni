const fib = (a, b, index, r_index) => {
    const c = a + b
    if (index === r_index) {
        return c
    }
    index++
    fib(b, c, index, r_index)
}

const r_index = 6


console.log(fib(1, 1, 3, r_index))
