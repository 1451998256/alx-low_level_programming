#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024

void print_elf_header_info(const unsigned char *header_data);
void print_magic(const unsigned char *magic_data);
void print_class(const unsigned char *header_data);
void print_data_encoding(const unsigned char *header_data);
void print_version(const unsigned char *header_data);
void print_os_abi(const unsigned char *header_data);
void print_abi_version(const unsigned char *header_data);
void print_file_type(const unsigned char *header_data);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <elf_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  unsigned char header_data[BUF_SIZE];
  ssize_t bytes_read = read(fd, header_data, BUF_SIZE);
  if (bytes_read < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  print_elf_header_info(header_data);

  if (close(fd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

void print_elf_header_info(const unsigned char *header_data) {
  const unsigned char *magic_data = header_data;
  print_magic(magic_data);

  const unsigned char *header_start = header_data + EI_NIDENT;
  print_class(header_start);
  print_data_encoding(header_start);
  print_version(header_start);
  print_os_abi(header_start);
  print_abi_version(header_start);
  print_file_type(header_start);
}

void print_magic(const unsigned char *magic_data) {
  printf("ELF Magic: ");
  for (int i = 0; i < EI_NIDENT; ++i) {
    printf("%02x ", magic_data[i]);
  }
  printf("\n");
}

void print_class(const unsigned char *header_data) {
  unsigned char class_byte = header_data[EI_CLASS];
  const char *class_str = "";
  switch (class_byte) {
    case ELFCLASS32:
      class_str = "ELF32";
      break;
    case ELFCLASS64:
      class_str = "ELF64";
      break;
    default:
      class_str = "<unknown>";
      break;
  }
  printf("Class: %s\n", class_str);
}

void print_data_encoding(const unsigned char *header_data) {
  unsigned char encoding_byte = header_data[EI_DATA];
  const char *encoding_str = "";
  switch (encoding_byte) {
    case ELFDATA2LSB:
      encoding_str = "2's complement, little endian";
      break;
    case ELFDATA2MSB:
      encoding_str = "2's complement, big endian";
      break;
    default:
      encoding_str = "<unknown>";
      break;
  }
  printf("Data: %s\n",
int main(int argc, char **argv)
{
    int fd;
    Elf64_Ehdr elf_header;

    if (argc != 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s <ELF_FILE>\n", argv[0]);
        exit(98);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
        exit(98);
    }

    if (read(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header))
    {
        dprintf(STDERR_FILENO, "Error: Cannot read ELF header\n");
        close_elf(fd);
        exit(98);
    }

    check_elf(elf_header.e_ident);
    print_magic(elf_header.e_ident);
    print_class(elf_header.e_ident);
    print_data(elf_header.e_ident);
    print_version(elf_header.e_ident);
    print_osabi(elf_header.e_ident);
    print_abi(elf_header.e_ident);
    print_type(elf_header.e_type, elf_header.e_ident);
    print_entry(elf_header.e_entry, elf_header.e_ident);

    close_elf(fd);
    return (0);
}
