#ifndef CANVAS_C
#define CANVAS_C


// n_colum = WIDTH of the image
// n_row =   HEIGHT of the image
//                               WIDTH         HEIGHT
Canvas create_canvas(int n_column, int n_row)
{
    Canvas myCanvas;
    myCanvas.width = n_column;
    myCanvas.height = n_row;

    myCanvas.pixelColor = (Tuple **)malloc(n_column * sizeof(Tuple *));

    for(int x = 0; x < n_column; x++)
    {
        // TODO: allocate once before the loop? if possible
        // allocate the memory for n_column in that row.
        myCanvas.pixelColor[x] =  (Tuple *) malloc(n_row * sizeof(Tuple));

        // initialize with zeros all the columns of that row.
        for(int y = 0; y < n_row; y++)
        {
           Tuple pixel = myCanvas.pixelColor[x][y];
           create_color(&pixel, 0.0, 0.0, 0.0);
        }
    }
    return myCanvas;
}

void write_pixel(Canvas * c, int x, int y, Tuple * color)
{
    if(x >= 0 && y >= 0)
    {
        if(x <= c->width  &&  y <= c->height)
        {
            c->pixelColor[x][y] = *color;
        }
    }
}

void canvas_to_ppmFile(Canvas * myCanvas)
{

    static int file_number = 0; //will increment every time it is called.
    file_number++;
    char file_name[] = {'i','m','a','g','e', file_number + '0','.','p','p','m','\0'};

    FILE * myFile;
    myFile = fopen(file_name, "w+");

    if(myFile != 0)
    {
        printf("The file %s was opened\n", file_name);

        // PPM header
        fprintf(myFile, "P3\n");
        fprintf(myFile, "# Created by Julie :D\n");
        fprintf(myFile, "%d %d\n", myCanvas->width, myCanvas->height);
        fprintf(myFile, "%d\n", MAX_COLOR_VALUE);

        // pixel value
        for(int y = 0; y < myCanvas->height; y++)
        {
            for(int x = 0; x < myCanvas->width; x++)
            {
                Tuple pixel = myCanvas->pixelColor[x][y];
                clamped_tuple_zero_one(&pixel);

                Tuple scaledColorPixel;
                multiply_tuple_by_value(&scaledColorPixel, &pixel, MAX_COLOR_VALUE);

                int r = get_red(&scaledColorPixel);
                int g = get_green(&scaledColorPixel);
                int b = get_blue(&scaledColorPixel);

                fprintf(myFile, "%d %d %d \n ", r, g, b);
            }
        }
    }
    else
    {
        printf("The file %s was not opened\n", file_name);
    }
    printf("The file %s was closed and is ready to be viewed!\n", file_name);
    fclose(myFile);
}

#endif /* CANVAS_C */
