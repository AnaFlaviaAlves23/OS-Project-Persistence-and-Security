#ifndef VSFS_CONTROL_H
#define VSFS_CONTROL_H

int find_free_bit(char *bitmap, int size);
int write_file(const char *disk_name, char *data, int data_len);
int read_file(const char *disk_name, int inode_idx);
void list_inodes(const char *disk_name);

#endif