library('R.matlab')

mat_data <- readMat('/home/braydan/uni/MXB362/Computer Lab/Code/week 6/aneurism.mat')

# Extract the volume data from the loaded data structure
Di <- mat_data$A

# Compute the maximum value in the volume
maxDi <- max(Di, na.rm = TRUE)

# Create an empty array to store the composited image
composited_image <- 0

# Loop through each element in the volume and perform front-to-back compositing
for (i in 1:length(Di)) {
  # Calculate the opacity value using the alpha transfer function
  alpha <- Di[i] / maxDi
  
  # Calculate the grey color intensity using the C transfer function
  C <- Di[i]
  
  # Perform front-to-back compositing
  composited_image <- composited_image + (1 - composited_image) * alpha * C
}

# Normalize the composited image for visualization
composited_image <- composited_image / max(composited_image, na.rm = TRUE)

# Plot the composited image
plot(composited_image, type = 'l', col = 'gray', main = 'Composited Volume Rendering of Aneurism Scan')
