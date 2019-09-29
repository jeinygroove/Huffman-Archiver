# Huffman-Archiver
Huffman Archiver, written on C++.

**Command line parameters**
   * `-c`: archive
   * `-u`: unarchive
   * `-f`, `--file <путь>`: name of input file
   * `-o`, `--output <путь>`: name of result file
   
**Output**

   The program displays compression/decompression statistics: the size of the source data, the size of the received data
   and the size that was used to store the additional data in the output file. All sizes in bytes.

   For example:
   ```
   $ ./huffman -c -f myfile.txt -o result.bin
   15678
   6172
   482
   ```

   Size of source file (source data): 15678 bytes, size of compressed data (without additional information):
6172 bytes, size of additional data: 482 bytes. The whole size of the compressed file: 6172 + 482 = 6654 bytes.
   
   ```
   $ ./huffman -u -f result.bin -o myfile_new.txt
   6172
   15678
   482
   ```
The size of the unpacked file (received data): 15678 bytes, the size of the compressed data (without additional information): 6172 bytes, size of additional data: 482 bytes. The whole size of the original compressed file: 6172 + 482 = 6654 bytes.
