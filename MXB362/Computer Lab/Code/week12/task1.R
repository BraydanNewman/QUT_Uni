# Step 1: Load the iris dataset
data(iris)

# Step 2: Produce a scatter plot matrix with color-coded species
pairs(iris[1:4],            # Select only the numeric dimensions
      main = "Scatterplot Matrix of Iris Dataset",
      pch = 21,             # Plotting character (circle with fill)
      bg = c("red", "green3", "blue")[unclass(iris$Species)],  # Color by species
      col = "black")        # Black border for points

# Step 3: Center the data by the mean value
iris_centered <- scale(iris[, 1:4], center = TRUE, scale = FALSE)

# Step 4: Calculate the covariance matrix
cov_matrix <- cov(iris_centered)

# Step 5: Calculate the eigenvalue decomposition of the covariance matrix
eigen_decomp <- eigen(cov_matrix)

# Extract eigenvalues and eigenvectors
eigenvalues <- eigen_decomp$values
eigenvectors <- eigen_decomp$vectors

# Step 6: Project the data onto the new basis vectors (Principal Components)
# We use the top 2 principal components
pc1 <- iris_centered %*% eigenvectors[, 1]
pc2 <- iris_centered %*% eigenvectors[, 2]

# Create a data frame with the projected data
projected_data <- data.frame(PC1 = pc1, PC2 = pc2, Species = iris$Species)

# Plot the projected data, color-coded by species
plot(projected_data$PC1, projected_data$PC2, 
     col = c("red", "green3", "blue")[unclass(projected_data$Species)],
     pch = 19, 
     xlab = "Principal Component 1",
     ylab = "Principal Component 2",
     main = "PCA of Iris Dataset")
legend("topright", legend = levels(iris$Species), 
       col = c("red", "green3", "blue"), pch = 19)