# Load the iris dataset, extract columns 1 and 2, and standardize
data(iris)
reduced_iris <- iris[, c(1, 2)]  # Extract Sepal Length and Sepal Width
reduced_iris_scaled <- scale(reduced_iris)  # Standardize to mean = 0, sd = 1

# Create a numerical species ID vector
species_id <- as.numeric(iris$Species)

# Define the Fisher's criterion function to maximize J(W)
fisher_criterion <- function(W) {
  # Normalize W
  W <- W / sqrt(sum(W^2))
  
  # Project the data onto W
  projected_data <- as.matrix(reduced_iris_scaled) %*% W
  
  # Calculate the means of the projected data for each class
  mean_class <- tapply(projected_data, species_id, mean)
  
  # Calculate the within-class scatter
  scatter_within <- sum(tapply(projected_data, species_id, function(x) sum((x - mean(x))^2)))
  
  # Calculate the between-class scatter
  mean_total <- mean(projected_data)
  scatter_between <- sum(table(species_id) * (mean_class - mean_total)^2)
  
  # Calculate J(W)
  J_W <- scatter_between / scatter_within
  return(-J_W)  # Negative because optim() performs minimization
}

# Use optim() to find the optimal W that maximizes J(W)
initial_W <- c(1, 1)  # Initial guess for W
optim_result <- optim(par = initial_W, fn = fisher_criterion)

# Extract optimal W and normalize it
optimal_W <- optim_result$par
optimal_W <- optimal_W / sqrt(sum(optimal_W^2))

# Calculate the value of J(W) for the optimal W
projected_data_optimal <- as.matrix(reduced_iris_scaled) %*% optimal_W
mean_class <- tapply(projected_data_optimal, species_id, mean)
scatter_within <- sum(tapply(projected_data_optimal, species_id, function(x) sum((x - mean(x))^2)))
mean_total <- mean(projected_data_optimal)
scatter_between <- sum(table(species_id) * (mean_class - mean_total)^2)
J_W_optimal <- scatter_between / scatter_within

# Report the results
cat("Optimal Projection Vector W:", optimal_W, "\n")
cat("Value of J(W):", J_W_optimal, "\n")


plot(reduced_iris_scaled[, 1], reduced_iris_scaled[, 2], 
     col = c("brown", "orange", "blue")[species_id], 
     pch = 19, 
     xlab = "Sepal Length (Standardized)", 
     ylab = "Sepal Width (Standardized)", 
     main = "Scatter Plot of Iris Data with Decision Boundary")

# Add decision boundary (assuming a line through origin for simplicity)
abline(a = 0, b = -optimal_W[2] / optimal_W[1], col = "black", lwd = 2)

# Load the iris dataset, extract columns 1 and 2, and standardize
data(iris)
reduced_iris <- iris[, c(1, 2)]  # Extract Sepal Length and Sepal Width
reduced_iris_scaled <- scale(reduced_iris)  # Standardize to mean = 0, sd = 1

# Create a numerical species ID vector
species_id <- as.numeric(iris$Species)

# Define the Fisher's criterion function to maximize J(W)
fisher_criterion <- function(W) {
  # Normalize W
  W <- W / sqrt(sum(W^2))
  
  # Project the data onto W
  projected_data <- as.matrix(reduced_iris_scaled) %*% W
  
  # Calculate the means of the projected data for each class
  mean_class <- tapply(projected_data, species_id, mean)
  
  # Calculate the within-class scatter
  scatter_within <- sum(tapply(projected_data, species_id, function(x) sum((x - mean(x))^2)))
  
  # Calculate the between-class scatter
  mean_total <- mean(projected_data)
  scatter_between <- sum(table(species_id) * (mean_class - mean_total)^2)
  
  # Calculate J(W)
  J_W <- scatter_between / scatter_within
  return(-J_W)  # Negative because optim() performs minimization
}

# Use optim() to find the optimal W that maximizes J(W)
initial_W <- c(1, 1)  # Initial guess for W
optim_result <- optim(par = initial_W, fn = fisher_criterion)

# Extract optimal W and normalize it
optimal_W <- optim_result$par
optimal_W <- optimal_W / sqrt(sum(optimal_W^2))

# Calculate the value of J(W) for the optimal W
projected_data_optimal <- as.matrix(reduced_iris_scaled) %*% optimal_W
mean_class <- tapply(projected_data_optimal, species_id, mean)
scatter_within <- sum(tapply(projected_data_optimal, species_id, function(x) sum((x - mean(x))^2)))
mean_total <- mean(projected_data_optimal)
scatter_between <- sum(table(species_id) * (mean_class - mean_total)^2)
J_W_optimal <- scatter_between / scatter_within

# Report the results
cat("Optimal Projection Vector W:", optimal_W, "\n")
cat("Value of J(W):", J_W_optimal, "\n")

# Visualize the projection of the iris data along the optimal projection vector W
# Set up the colors for each species
colors <- c("red", "green3", "blue")
species_labels <- levels(iris$Species)

# Plot histogram for each species to visualize separation along the projection vector
hist(projected_data_optimal[species_id == 1], 
     col = colors[1], 
     main = "Projection of Iris Data along Optimal W",
     xlab = "Projection Value",
     xlim = range(projected_data_optimal), 
     ylim = c(0, 25),
     breaks = 10,
     freq = TRUE,
     border = "black")
hist(projected_data_optimal[species_id == 2], 
     col = colors[2], 
     add = TRUE, 
     breaks = 10,
     freq = TRUE,
     border = "black")
hist(projected_data_optimal[species_id == 3], 
     col = colors[3], 
     add = TRUE, 
     breaks = 10,
     freq = TRUE,
     border = "black")

legend("topright", legend = species_labels, fill = colors)
