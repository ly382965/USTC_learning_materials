x = 0:2*pi/1023:2*pi;
y = 255/2.0*(1+sin(x));
sin_table = uint8(y);
fid = fopen('mystorage.mif','w');
fprintf(fid,'WIDTH=8;\n');
fprintf(fid,'DEPTH=1024;\n\n');
fprintf(fid,'ADDRESS_RADIX=UNS;\n\n');
fprintf(fid,'DATA_RADIX=UNS;\n\n');
fprintf(fid,'CONTENT BEGIN \n \t0\t:\t');
for k = 1:1024
    fprintf(fid,'%d\t',sin_table(k));
    if(k<1024)fprintf(fid,';\n\t%d\t:\t',k);end
end
fprintf(fid,';\nEND;');
fclose(fid);