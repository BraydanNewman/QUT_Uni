# Custom Options
options(timeout=2000) # I have Really Really bad Internet, Damn You Telstra and Opticomm
options(repos=c(CRAN="https://cran.csiro.au/")) # For stability I set a mirror, if you have a preferred one, comment out line
knitr::opts_chunk$set(warning = FALSE, message = FALSE) # Turn Off Messages and Warnings

# Install Libraries (Only if they are not already installed)
if (!require("drat")) install.packages("drat")
if (!require("ggplot2")) install.packages("ggplot2")
if (!require("tidyverse")) install.packages("tidyverse")
if (!require("formatR")) install.packages("formatR")
if (!require("formatR")) install.packages("formatR")
if (!require("tidytuesdayR")) install.packages("tidytuesdayR")
if (!require("reshape2")) install.packages("reshape2")
if (!require("ggiraphExtra")) install.packages("ggiraphExtra")
if (!require("igraph")) install.packages("igraph")
if (!require("network")) install.packages("network")
if (!require("sna")) install.packages("sna")
if (!require("ndtv")) install.packages("ndtv")
if (!require("EpiContactTrace")) install.packages("EpiContactTrace")
if (!require("RColorBrewer")) install.packages("RColorBrewer")
if (!require("viridis")) install.packages("viridis")
if (!require("circlize")) install.packages("circlize")
if (!require("alluvial")) install.packages("alluvial")
if (!require("ggrepel")) install.packages("ggrepel")
if (!require("ggsankeyfier")) install.packages("ggsankeyfier")
if (!require("rnaturalearth")) install.packages("rnaturalearth")
if (!require("rnaturalearthdata")) install.packages("rnaturalearthdata")
if (!require("ggspatial")) install.packages("ggspatial")
if (!require("maps")) install.packages("maps")
if (!require("sf")) install.packages("sf")
if (!require("cartogram")) install.packages("cartogram")
if (!require("sp")) install.packages("sp")
if (!require("spData")) install.packages("spData")
if (!require("raster")) install.packages("raster")
if (!require("patchwork")) install.packages("patchwork")

# Load Libraries
library(drat)
library(ggplot2)
library(tidyverse)
library(dplyr)
library(magrittr)
library(formatR)
library(tidytuesdayR)
library(reshape2)
library(ggalluvial)
library(ggiraphExtra)
library(igraph)
library(network)
library(sna)
library(ndtv)
library(EpiContactTrace)
library(RColorBrewer)
library(viridis)
library(circlize)
library(alluvial)
library(ggrepel)
library(ggsankeyfier)
library(rnaturalearth)
library(rnaturalearthdata)
library(ggspatial)
library(sf)
library(maps)
library(cartogram)
library(sp)
library(spData)
library(raster)
library(terra)
library(patchwork)



# Add Extra Data Repo's
drat::addRepo("kjhealy")
drat::addRepo("doehm")

# Install Extra data packages
if (!require("covdata")) install.packages("covdata")
if (!require("survivoR")) install.packages("survivoR")

# Extra Data 
# **!! DO NOT MUTATE THIS DATA !!**
# This data is like this to stop repeated download as Github Rate limited me. DAMN YOU GITHUB
# Thus if this data is mutated it will stay mutated and not get refreshed
# To fix mutated data clear the data and re-run 
if(!exists("gender_pay_gap_data")) {
  gender_pay_gap_data <- read.csv("https://raw.githubusercontent.com/plotly/datasets/master/school_earnings.csv")
}
if(!exists("people_migration_data")) people_migration_data <- read.table("https://raw.githubusercontent.com/holtzy/data_to_viz/master/Example_dataset/13_AdjacencyDirectedWeighted.csv", header=TRUE)
if(!exists("tuesdata")) tuesdata <- tidytuesdayR::tt_load(2021, week = 15)

plant_1 = projectRaster(raster("data/invasive_plants/sumrast_allassumptions.avg_Alliaria petiolata.tif"), crs = crs("+init=epsg:4326"))
plant_2 = projectRaster(raster("data/invasive_plants/sumrast_allassumptions.avg_Rosa multiflora.tif"), crs = crs("+init=epsg:4326"))

plants = stack(plant_1, plant_2)

col <- c("darkgrey", viridis::plasma(n = 4))
brk <- c(0, 0.2, 0.4, 0.6, 0.8, 1)

par(xpd = FALSE)
par(oma = c(0.5, 0.5, 4, 6))
plot(x = plants, 
     breaks=brk, 
     main=c('Alliaria Petiolata', 'Rosa Multiflora'), 
     col=col, 
     legend = FALSE)
par(xpd = TRUE)
par(oma = c(2, 2, 2, 2))
legend(x = 0.85, y = 1, title="Plant Density", legend = c("Low/None", "Semi Low", "Medium", "Semi High", "Very high"), fill = col)
title("Invasive Plants spread in Minnesota", line = 3)



cell_size<-area(plant_1, na.rm=TRUE, weights=FALSE)
cell_size<-cell_size[!is.na(cell_size)]
raster_area<-length(cell_size)*median(cell_size)

plant_1_area = (sum(values(plant_1) > 0.2, na.rm=TRUE) / sum(values(plant_1) <= 1, na.rm=TRUE)) 
plant_1_area_rest = 1 - plant_1_area
plant_2_area = (sum(values(plant_2) > 0.2, na.rm=TRUE) / sum(values(plant_2) <= 1, na.rm=TRUE)) 
plant_2_area_rest = 1 - plant_2_area

plant_1_area_dataframe <- data.frame(
  class = c('Covered', 'Not Yet Covered'),
  n = c(plant_1_area, plant_1_area_rest)
)

plant_2_area_dataframe <- data.frame(
  class = c('Rosa Multiflora', 'Not Yet Invaded'),
  n = c(plant_2_area, plant_2_area_rest)
)

colours = c("red", "darkgreen")

plant_1_pie = ggplot(plant_1_area_dataframe, aes(x="", y=n, fill=class)) +
  geom_bar(stat="identity", width=1) +
  coord_polar("y", start=0) +
  theme(plot.title = element_text(hjust = 0.5)) +
  labs(x ="", y = "",
       fill = "",
       title = "Area Covered by Alliaria Petiolata") +
  scale_fill_manual(values = colours)

plant_2_pie = ggplot(plant_2_area_dataframe, aes(x="", y=n, fill=reorder(class, n))) +
  geom_bar(stat="identity", width=1) +
  coord_polar("y", start=0) +
  theme(plot.title = element_text(hjust = 0.5)) +
  labs(x ="", y = "",
       fill = "",
       title = "Area Covered by Rosa Multiflora") +
  scale_fill_manual(values = colours)
  
plant_1_pie + plant_2_pie +
  plot_annotation(title = "Area of Spread of Diffrent Invasive plants") & 
  theme(legend.position = "top", plot.title = element_text(hjust = 0.5))


