#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);

/**
 * check_elf - Checks if a file is an ELF file.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: If the file is not an ELF file - exit code 98.
 */
void check_elf(unsigned char *e_ident)
{
    int index;

    for (index = 0; index < 4; index++)
    {
        if (e_ident[index] != 127 &&
            e_ident[index] != 'E' &&
            e_ident[index] != 'L' &&
            e_ident[index] != 'F')
        {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

/**
 * print_magic - Prints the magic numbers of an ELF header.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void print_magic(unsigned char *e_ident)
{
    int index;

    printf("  Magic:   ");
    for (index = 0; index < EI_NIDENT; index++)
    {
        printf("%02x", e_ident[index]);
        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }
}

/**
 * print_class - Prints the class of an ELF header.
 * @e_ident: A pointer to an array containing the ELF class.
 */
void print_class(unsigned char *e_ident)
{
    printf("  Class:                             ");
    switch (e_ident[EI_CLASS])
    {
    case ELFCLASSNONE:
        printf("none\n");
        break;
    case ELFCLASS32:
        printf("ELF32\n");
        break;
    case ELFCLASS64:
        printf("ELF64\n");
        break;
    default:
        printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }
}

/**
 * print_data - Prints the data of an ELF header.
 * @e_ident: A pointer to an array containing the ELF class.
 */
void print_data(unsigned char *e_ident)
{
    printf("  Data:                              ");
    switch (e_ident[EI_DATA])
    {
    case ELFDATANONE:
        printf("none\n");
        break;
    case ELFDATA2LSB:
        printf("2's complement, little endian\n");
        break;
    case ELFDATA2MSB:
        printf("2's complement, big endian\n");
        break;
    default:
        printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }
}

/**
 * print_version - Prints the version of
/**

print_entry - Prints the entry point of an ELF header.
@e_entry: The ELF entry point.
@e_ident: A pointer to an array containing the ELF class.
*/
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
if (e_ident[EI_CLASS] == ELFCLASS32)
printf(" Entry point address: %#x\n", (unsigned int)e_entry);
else if (e_ident[EI_CLASS] == ELFCLASS64)
printf(" Entry point address: %#lx\n", e_entry);
}
/**

close_elf - Closes an ELF file.
@elf: The file descriptor of the ELF file.
*/
void close_elf(int elf)
{
if (close(elf))
{
dprintf(STDERR_FILENO, "Error: Cannot close ELF file descriptor\n");
exit(98);
}
}
/**

main - Entry point.

@argc: The argument count.

@argv: The argument vector.

Return: 0 on success.
*/
int main(int argc, char **argv)
{
int elf, read_count;
unsigned char e_ident[EI_NIDENT];

if (argc != 2)
{
dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", argv[0]);
exit(98);
}

elf = open(argv[1], O_RDONLY);

if (elf == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read ELF file\n");
exit(98);
}

read_count = read(elf, e_ident, EI_NIDENT);

if (read_count < EI_NIDENT)
{
dprintf(STDERR_FILENO, "Error: Cannot read ELF file\n");
exit(98);
}

check_elf(e_ident);
printf("ELF Header:\n");
print_magic(e_ident);
print_class(e_ident);
print_data(e_ident);
print_version(e_ident);
print_abi(e_ident);
print_type(0, e_ident);

if (lseek(elf, (off_t)0, SEEK_SET) == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read ELF file\n");
close_elf(elf);
exit(98);
}

close_elf(elf);
return (0);
}
