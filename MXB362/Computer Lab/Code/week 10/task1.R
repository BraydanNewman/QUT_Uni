library(pracma)   
library(ggplot2)  
library(ggquiver)
library(tidyverse)

sp = 0.1

x_points = seq(-2, 2, by = sp)
y_points = seq(-1.5, 1.5, by = sp)

X = matrix(x_points, nrow = length(y_points), ncol = length(x_points), byrow=TRUE)
Y = matrix(y_points, nrow = length(y_points), ncol = length(x_points), byrow=FALSE)

xy_pairs = unique(expand.grid(x = as.vector(X), y = as.vector(Y)))


z = function(x){ x[1] * exp(-x[1]^2 - x[2]^2) }

Z = matrix(apply(data.frame(xy_pairs),1,FUN=z),nrow = length(y_points), ncol = length(x_points),byrow = TRUE)

Vx = gradient(Z,h1 = sp, h2 = sp)$X
Vy = gradient(Z,h1 = sp, h2 = sp)$Y



# Create a data frame for ggplot visualization
df = expand.grid(x = x_points, y = y_points)
df$Vx = as.vector(Vx)
df$Vy = as.vector(Vy)

# Visualize using ggplot and geom_quiver
ggplot(df, aes(x = x, y = y, u = Vx, v = Vy)) +
  geom_quiver() +
  theme_minimal() +
  labs(title = "Vector Field Visualization of the Landscape",
       x = "X Coordinate",
       y = "Y Coordinate")




