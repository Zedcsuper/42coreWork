#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 521

static int ft_strlen(const char *s)
{
    int i = 0;
    while (s && s[i])
        i++;
    return i;
}

static char *ft_strjoin(char *s1, char *s2)
{
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    for (int i = 0; i < len1; i++)
        result[i] = s1[i];
    for (int i = 0; i < len2; i++)
        result[len1 + i] = s2[i];
    result[len1 + len2] = '\0';
    free(s1); // Free the old buffer to prevent memory leaks
    return result;
}

static char *ft_strchr(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return (c == '\0') ? (char *)s : NULL;
}

static char *fill_buffer(int fd, char *buffer)
{
    char temp[BUFFER_SIZE + 1];
    int bytes_read;

    bytes_read = read(fd, temp, BUFFER_SIZE);
    if (bytes_read <= 0)
        return buffer;
    temp[bytes_read] = '\0';
    return ft_strjoin(buffer, temp);
}

static char *extract_line(char *buffer)
{
    if (!buffer || !*buffer)
        return NULL;
    int i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    char *line = malloc(i + 2);
    if (!line)
        return NULL;
    for (int j = 0; j < i; j++)
        line[j] = buffer[j];
    if (buffer[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return line;
}

static char *update_buffer(char *buffer)
{
    if (!buffer)
        return NULL;
    char *newline_pos = ft_strchr(buffer, '\n');
    if (!newline_pos)
    {
        free(buffer);
        return NULL;
    }
    char *new_buffer = malloc(ft_strlen(newline_pos + 1) + 1);
    if (!new_buffer)
    {
        free(buffer);
        return NULL;
    }
    int i = 0;
    while (newline_pos[++i])
        new_buffer[i - 1] = newline_pos[i];
    new_buffer[i - 1] = '\0';
    free(buffer);
    return new_buffer;
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer = fill_buffer(fd, buffer);
    if (!buffer)
        return NULL;
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
    return line;
}

int main()
{
    int fd = open("txt.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
