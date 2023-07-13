#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <libavformat/avformat.h>

#define MAX_PATH_LENGTH 256

int is_audio_file(const char *filename) {
    const char *extensions[] = {".wav", ".mp3", ".flac", ".ogg"};

    for (int i = 0; i < sizeof(extensions) / sizeof(extensions[0]); i++) {
        if (strstr(filename, extensions[i]) != NULL)
            return 1;
    }

    return 0;
}

void convertSecondsToHoursAndMinutes(double seconds, int *hours, int *minutes) {
    *hours = (int)(seconds / 3600);
    seconds -= (*hours * 3600);
    *minutes = (int)(seconds / 60);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <folder>\n", argv[0]);
        return 1;
    }

    char folder_path[MAX_PATH_LENGTH];
    strncpy(folder_path, "", MAX_PATH_LENGTH - 1);

    for (int i = 1; i < argc; i++) {
        strncat(folder_path, argv[i], MAX_PATH_LENGTH - strlen(folder_path) - 1);
        strncat(folder_path, " ", MAX_PATH_LENGTH - strlen(folder_path) - 1);
    }

    folder_path[strlen(folder_path) - 1] = '\0';

    DIR *dir;
    struct dirent *entry;

    dir = opendir(folder_path);
    if (dir == NULL) {
        printf("Failed to open folder: %s\n", folder_path);
        return 1;
    }

    av_log_set_level(AV_LOG_QUIET);

    avformat_network_init();

    AVFormatContext *format_ctx;
    double total_duration = 0.0;

    while ((entry = readdir(dir)) != NULL) {
        char file_path[MAX_PATH_LENGTH];
        snprintf(file_path, MAX_PATH_LENGTH, "%s/%s", folder_path, entry->d_name);

        if (is_audio_file(entry->d_name)) {
            format_ctx = avformat_alloc_context();
            if (avformat_open_input(&format_ctx, file_path, NULL, NULL) == 0) {
                if (avformat_find_stream_info(format_ctx, NULL) >= 0) {
                    int64_t duration = format_ctx->duration;
                    double duration_secs = (double)duration / AV_TIME_BASE;
                    total_duration += duration_secs;
                } else {
                    fprintf(stderr, "Failed to find stream information for file: %s\n", file_path);
                }
                avformat_close_input(&format_ctx);
            } else {
                fprintf(stderr, "Failed to open input file: %s\n", file_path);
            }
            avformat_free_context(format_ctx);
        }
    }

    closedir(dir);
 int hours, minutes;
    convertSecondsToHoursAndMinutes(total_duration, &hours, &minutes);

    printf("Total duration of audio files in '%s': %d hours, %d minutes\n", folder_path, hours, minutes);

    return 0;
}

