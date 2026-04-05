#include "myfile.h"

void print_elf_type(uint16_t e_type) {
    const char *type_str;
    switch (e_type) {
    case ET_NONE:
      type_str = "Unknown (ET_NONE)";
      break;
    case ET_REL:
      type_str = "Relocatable (ET_REL)";
      break;
    case ET_EXEC:
      type_str = "Executable (ET_EXEC)";
      break;
    case ET_DYN:
      type_str = "Shared Object/PIE (ET_DYN)";
      break;
    case ET_CORE:
      type_str = "Core Dump (ET_CORE)";
      break;
    default:
      if (e_type >= ET_LOOS && e_type <= ET_HIOS)
        type_str = "OS-Specific";
      else if (e_type >= ET_LOPROC && e_type <= ET_HIPROC)
        type_str = "Processor-Specific";
      else
        type_str = "Invalid";
    }
    printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int __cmd_myfile(const char* filename) {
    char filepath[256];
    int fd;
    Elf64_Ehdr ehdr;

    strcpy(filepath, filename);
    fflush(stdout);
    printf("filepath: %s\n", filepath);

    fd = open(filepath, O_RDONLY);
    if (fd < 0) {
      const char *prefix = "/workspace/exercises/20_mybash/";
      size_t prefix_len = strlen(prefix);
      if (strncmp(filepath, prefix, prefix_len) == 0) {
        fd = open(filepath + prefix_len, O_RDONLY);
      }
    }

    if (fd < 0) {
      perror("open");
      return 1;
    }

    if (read(fd, &ehdr, sizeof(ehdr)) != (ssize_t)sizeof(ehdr)) {
      perror("read");
      close(fd);
      return 1;
    }

    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 || ehdr.e_ident[EI_MAG3] != ELFMAG3) {
      fprintf(stderr, "%s is not an ELF file\n", filepath);
      close(fd);
      return 1;
    }

    print_elf_type(ehdr.e_type);
    close(fd);
    return 0;
}