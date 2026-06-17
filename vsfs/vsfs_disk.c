#include "vsfs.h"
#include "vsfs_disk.h"

int get_inode_sector(int number, int inode_start_address) {
    return inode_start_address + (number * sizeof(struct inode)) / BLOCK_SIZE;
}