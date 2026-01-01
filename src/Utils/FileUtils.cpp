#include <FileUtils.h>

string FileUtils::ReadFile(const char* InFilePath)
{
    FILE* File = fopen(InFilePath, "rb");

    if (!File)
    {
        cout << "Could not open file " << InFilePath << endl;
        return string();
    }

    // Go to the end.
    fseek(File, 0, SEEK_END);

    // Get size
    long Size = ftell(File);

    // Rewind the file
    std::rewind(File);

    if (Size < 0)
    {
        fclose(File);
        cout << "Count not retrieve file size of " << InFilePath << endl;
        return string();
    }

    string Buffer(static_cast<size_t>(Size), '\0');

    size_t Read = fread(&Buffer[0], 1, Buffer.size(), File);

    // Read size should be same as buffer size.
    if (Read != Buffer.size())
    {
        cout << "Mismatch reading file with file size with " << InFilePath << endl;
        return string();
    }

    return Buffer;
}
