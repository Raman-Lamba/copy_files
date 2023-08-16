#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void copyFile(const char* sourcePath, const char* destinationPath) {
    int sourceFile = open(sourcePath, O_RDONLY);
    if (sourceFile == -1) {
        perror("Error opening source file");
        return;
    }

    int destFile = open(destinationPath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (destFile == -1) {
        perror("Error opening destination file");
        close(sourceFile);
        return;
    }

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) {
        if (write(destFile, buffer, bytesRead) == -1) {
            perror("Error writing to destination file");
            break;
        }
    }

    close(sourceFile);
    close(destFile);

    if (bytesRead == -1) {
        perror("Error reading from source file");
    } else {
        std::cout << "File copy completed successfully." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " source_file destination_file" << std::endl;
        return 1;
    }

    const char* sourcePath = argv[1];
    const char* destinationPath = argv[2];

    copyFile(sourcePath, destinationPath);

    return 0;
}
