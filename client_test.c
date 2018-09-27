//// Copyright (c) 2018 Electric Power Research Institute, Inc.
//// author: Mark Slicker <mark.slicker@gmail.com>

// this is a hack to keep the bash script from failing, we have stuffed all
// the functionality of the der_client and  into the se_core.o file
// in order to share them and don't want
// redefined functionality from this file

int main (int argc, char **argv) { }
