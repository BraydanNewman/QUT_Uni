library(ggplot2)
library(grid)

Vx <- readRDS("/home/braydan/uni/MXB362/Computer Lab/Code/week 10/Vx.RDS")
Vy <- readRDS("/home/braydan/uni/MXB362/Computer Lab/Code/week 10/Vy.RDS")

grid_size <- 400
x_vals <- seq(1, grid_size, by = 15) # Define regular grid step for seed points
y_vals <- seq(1, grid_size, by = 15) # Seed points every 20 units for example

# Create a set of seed points
seed_points <- expand.grid(x = x_vals, y = y_vals)


generate_streamline_bidirectional <- function(seed_x, seed_y, Vx, Vy, h = 0.5, max_steps = 100) {
  # Initialize lists to hold streamline paths for forward and backward directions
  forward_path_x <- c()
  forward_path_y <- c()
  backward_path_x <- c()
  backward_path_y <- c()
  
  # Function to follow streamline in a specified direction
  follow_streamline <- function(x, y, direction = 1) {
    path_x <- c()
    path_y <- c()
    
    for (i in 1:max_steps) {
      # Check if we're still inside the grid
      if (x >= 1 && y >= 1 && x <= grid_size && y <= grid_size) {
        # Append current position to the path
        path_x <- c(path_x, x)
        path_y <- c(path_y, y)
        
        # Get velocity values at the current position, scaled by direction
        dx <- direction * h * Vx[round(x), round(y)]
        dy <- direction * h * Vy[round(x), round(y)]
        
        # Update position
        x <- x + dx
        y <- y + dy
        
        # Break if outside the grid boundary
        if (x < 1 || x > grid_size || y < 1 || y > grid_size) {
          break
        }
      } else {
        break
      }
    }
    return(list(x = path_x, y = path_y))
  }
  
  # Generate forward and backward streamlines
  forward <- follow_streamline(seed_x, seed_y, direction = 1)
  backward <- follow_streamline(seed_x, seed_y, direction = -1)
  
  # Combine forward and backward streamlines
  combined_x <- c(rev(backward$x), forward$x)
  combined_y <- c(rev(backward$y), forward$y)
  
  return(list(x = combined_x, y = combined_y))
}


h <- 0.4      # Step size to control smoothness of streamlines
max_steps <- 200  # Maximum number of steps per streamline

# Generate and plot streamlines for each seed point
plot(1:grid_size, 1:grid_size, type = "n", xlab = "x", ylab = "y", main = "Streamlines with Bidirectional Paths")

# Iterate over each seed point
for (i in 1:nrow(seed_points)) {
  seed_x <- seed_points$x[i]
  seed_y <- seed_points$y[i]
  
  # Generate bidirectional streamline
  streamline <- generate_streamline_bidirectional(seed_x, seed_y, Vx, Vy, h = h, max_steps = max_steps)
  
  # Plot the streamline only if it has valid points
  if (length(streamline$x) > 1) {
    lines(streamline$x, streamline$y, col = "blue")
  }
}


