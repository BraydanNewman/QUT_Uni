clear all
figure

filename = 'stag_beetle_832x832x494_uint16.raw';
width = 832;
height = 494;
depth = 832;
datatype = 'uint16';

fileID = fopen(filename, "r");

volume = fread(fileID, width * height * depth, datatype);

fclose(fileID);

volume = reshape(volume, [width, depth, height]);

min_val = min(volume(:));
max_val = max(volume(:));

isovalue = 100;

h = isosurface(volume, isovalue)

p = patch(h, 'FaceColor', 'red', 'edgecolor', 'none');

camlight
lighting gouraud
axis vis3d off
set(gcf,'color','w')
