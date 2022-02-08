// #ifndef NULL
// #define NULL 0
// #endif
// typedef unsigned int Uint32;

// extern void *(*drb_symbol_lookup)(const char *sym);
// typedef void (*drb_upload_pixel_array_fn)(const char *name, const int w, const int h, const Uint32 *pixels);

int summation(int *arr, int size)
{
    int summation = 0;
    size--;
    for (; size > -1; size--)
    {
        summation += arr[size]; 
    }
    return summation;
}

// void make_noise_texture(Uint32 *pixels, int width, int height)
// {
//     static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;

//     if (!drb_upload_pixel_array) 
//     {
//         drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
//         if (!drb_upload_pixel_array) 
//         {
//             return;  // oh well.
//         }
//     }

//     // Send it to the renderer to create/update a sprite.
//     drb_upload_pixel_array("noise_texture", width, height, pixels);
// }