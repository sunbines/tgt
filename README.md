## Introduction
The Linux target framework (tgt) is a user space SCSI target framework
that supports the iSCSI and iSER transport protocols and that supports
multiple methods for accessing block storage. Tgt consists of
user-space daemon and tools.

Currently, tgt supports the following SCSI transport protocols:
- iSCSI software target driver for Ethernet NICs
- iSER software target driver for Infiniband and RDMA NICs

Tgt supports the following methods for accessing local storage:
- aio, the asynchronous I/O interface also known as libaio.
- rdwr, smc and mmc, synchronous I/O based on the pread() and pwrite()
  system calls.
- null, discards all data and reads zeroes.
- ssc, SCSI tape support.
- sg and bsg, SCSI pass-through.
- glfs, the GlusterFS network filesystem.
- rbd, Ceph's distributed-storage RADOS Block Device.
- sheepdog, a distributed object storage system.

Tgt can emulate the following SCSI device types:
- SBC: a virtual disk drive that can use a file to store the content.
- SMC: a virtual media jukebox that can be controlled by the "mtx"
  tool.
- MMC: a virtual DVD drive that can read DVD-ROM iso files and create
  burnable DVD+R. It can be combined with SMC to provide a fully
  operational DVD jukebox.
- SSC: a virtual tape device (aka VTL) that can use a file to store
  the content.
- OSD: a virtual object-based storage device that can use a file to
  store the content (in progress).


## License
The code is released under the GNU General Public License version 2.


## Requirements
Target drivers have their own ways to build, configure, etc. Please
find an appropriate documentation in the doc directory.


## Developer Notes
The central communication channel for tgt development is the mailing list
(<stgt@vger.kernel.org>).

First, please read the following documents (in short, follow Linux
kernel development rules):

- https://www.kernel.org/doc/Documentation/process/coding-style.rst
- https://www.kernel.org/doc/Documentation/process/submitting-patches.rst

Then, check your patches with the patch style checker prior to
submission (scripts/checkpatch.pl) like the following example.

fujita@arbre:~/git/tgt$ ./scripts/checkpatch.pl ~/0001-add-bidi-support.patch
Your patch has no obvious style problems and is ready for submission.
