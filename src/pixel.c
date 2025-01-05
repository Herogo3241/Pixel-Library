#include "pixel.h"

int width, height, maxvalue = 255;
uint8_t **rChannel, **gChannel, **bChannel;

void startCanvas(int canvasWidth, int canvasHeight){
    width = canvasWidth;
    height = canvasHeight;
    

    // creating the matrix based on window size;
    rChannel = (uint8_t **)malloc((height) * sizeof(uint8_t*));
    gChannel = (uint8_t **)malloc((height) * sizeof(uint8_t*));
    bChannel = (uint8_t **)malloc((height) * sizeof(uint8_t*));

    if (!rChannel || !gChannel || !bChannel){
        perror("Window Creation Failure");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < height; i++){
        rChannel[i] = (uint8_t *)malloc((width) * sizeof(uint8_t));
        gChannel[i] = (uint8_t *)malloc((width) * sizeof(uint8_t));
        bChannel[i] = (uint8_t *)malloc((width)* sizeof(uint8_t));
        if (!rChannel[i] || !gChannel[i] || !bChannel){
            perror("Window Creation Failure");
            exit(EXIT_FAILURE);
        }
    }


}

void setPixel(Vec2 pos, Color color){
    if (pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height){
        printf("Out of bounds coordinate");
        exit(EXIT_FAILURE);
    }

    //setting the  pixel
    rChannel[height - pos.y - 1][pos.x] = color.r; 
    gChannel[height - pos.y - 1][pos.x] = color.g;
    bChannel[height - pos.y - 1][pos.x] = color.b;   
}



void display(){
    FILE *out = fopen("temp.ppm", "w");
    fprintf(out, "P6 %d %d %d\n", width, height, maxvalue);

    for (size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            fwrite(&rChannel[i][j], sizeof(uint8_t), 1, out);
            fwrite(&gChannel[i][j], sizeof(uint8_t), 1, out);
            fwrite(&bChannel[i][j], sizeof(uint8_t), 1, out);
        }
    }

    fclose(out);

    int display_status = system("display temp.ppm");
    if (display_status == -1)
        perror("Display issue");

}

void animate(int frameNo){
    char* folderName = "temp";
    struct stat st = {0};

    if (stat(folderName, &st)){
        if(mkdir(folderName, 0777) != 0){
            perror("Animation Error");
            exit(EXIT_FAILURE);
        }
    }

    char tempFile[256];
    snprintf(tempFile, sizeof(tempFile), "temp/temp%05d.ppm", frameNo);
    FILE *out = fopen(tempFile, "w");
    fprintf(out, "P6 %d %d %d\n", width, height, maxvalue);

    for (size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            fwrite(&rChannel[i][j], sizeof(uint8_t), 1, out);
            fwrite(&gChannel[i][j], sizeof(uint8_t), 1, out);
            fwrite(&bChannel[i][j], sizeof(uint8_t), 1, out);
        }
    }

    fclose(out);

}

void saveVideo (const char* fileName, int frameRate){
    char command[1024];
    snprintf(command, sizeof(command), "ffmpeg -framerate %d -i temp/temp%%05d.ppm -c:v libx264 -pix_fmt yuv420p %s", frameRate, fileName);
    int video_status = system(command);
    system("rm -rf temp");
    if (video_status == -1){
        perror("Video Generation Error");
        exit(EXIT_FAILURE);
    }
    memset(command, '\0', 1024);
    snprintf(command, sizeof(command), "ffplay %s", fileName);
    int play_status = system(command);
    if (play_status == -1){
        perror("Video Play Error");
        exit(EXIT_FAILURE);
    }
}

void saveAsImage(const char* filename) {
    char command[256];  // Ensure the command buffer is large enough
    snprintf(command, sizeof(command), "convert temp.ppm %s", filename);  // Format the command string
    int conversion_status = system(command);  // Execute the command
    if (conversion_status == -1){
        system("rm temp.ppm");
        perror("Conversion Error");
        exit(EXIT_FAILURE);
    }
}



void endCanvas() {
    for(int i = 0; i < height; i++){
       free(rChannel[i]);
       free(gChannel[i]);
       free(bChannel[i]);
    }

    free(rChannel);
    free(gChannel);
    free(bChannel);


    system("rm temp.ppm");

}

