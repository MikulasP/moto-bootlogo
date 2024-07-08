# Motorola logo.bin structure

### Scope of this document

This document describes the structure of the logo.bin files that Motorola uses on their phones.

### References

Motorola uses a somewhat different logo partition structure, but not much documentation is available about it.
For reference we can use these projects to learn more about Motorola's logo file structure:
* [MotoBootLogoMaker](https://github.com/CaitSith2/MotoBootLogoMaker/tree/master)
* [moto-bootlogo](https://github.com/eriktim/moto-bootlogo)

## 1. The Android boot logo

The boot logo is contained into a dedicated partition called logo, you can find the binary image called logo.bin packed into the stock ROM archive or you can download it from the phone using the SP Flash Tool program.

The partition image contains several different pictures, some are at full screen size, others are snippets used (before the actual boot stage) to represent e.g. the charging battery, the percentage, etc. The logo.bin has a rather simple structure:

|Content|Size (bytes)|Note|
|-|-|-|
|**MTK Header**|512|At offset **0x08** there should be the string **LOGO** or **logo**.|
|**Picture count**|4|A **little-endian** 32bit integer. This is the number of pictures packed into the data block.|
|**Total Block Size**|4|A little-endian 32bit integer. This is the total size of the data, excluding only the 512 bytes of the MTK header.|
|**Offset Map**|4 * count|For each picture there is a little-endian 32bit integer, indicating the offset of the picture into the data, after the 512 bytes header. The first offset is 4 + 4 + (4 * pictures count).|
|**Pictures Data Block**|Variable|Each picture is in **raw RGB** format, it is appended as a **z-compressed** file.|
<sub><sup>Table 1.1</sup></sub>
>Source: [Android Boot Logo and Bootanimation](https://www.rigacci.org/wiki/doku.php/doc/appunti/android/logo_bootanimation)

## 2. Motorola logo

### Structure of the Motorola logo.bin:

|Content|Size (bytes)|Note|
|-|-|-|
|**Header prefix**|13|The first 13 bytes define the header's prefix.  (Table 2.1)|
|**Header**|1024 - 13|Contains a 24 byte long header for each picture. The total length is 1024 byte, but the actual content's length is variable. (Table 2.2)|
|**Pictures Data Block**|Variable|Each picture has it's own length given by it's header, but every picture is padded with **0xFF** values to a multiple of 1024. (Table 2.3)|
<sub><sup>Table 2.1</sup></sub>

### Individual sections in detail

#### Header prefix

|Content|Size (bytes)|Note|
|-|-|-|
|**"MotoLogo\0"**|9|The first 9 byte must be "MotoLogo" and a 0x00 sentinel character.|
|**Header length**|2|Specifies the header's actual length in LSB order. The length includes the first 13 bytes of prefix too.|
|**0**|2|2 bytes of zero ¯\\\_(ツ)_/¯ |
<sub><sup>Table 2.2</sup></sub>

#### Header

The rest of the header is composed of 32 byte long sections in the above format:

|Content|Size (bytes)|Note|
|-|-|-|
|**Image name**|24|The name of the image.|
|**Data Offset**|4|Image start offset from the beginning of the file in MSB order.|
|**Data Size**|4|Image's actual length (Including prefix string and resolution) in MSB order.|
<sub><sup>Table 2.3</sup></sub>

#### Image

|Content|Size (bytes)|Note|
|-|-|-|
|**"MotoRun\0"**|8|The first 8 byte must be "MotoRun" and a 0x00 sentinel character.|
|**Image width**|2|The image's width in pixels in MSB order.|
|**Image height**|2|The image's height in pixels in MSB order.|
|**Image Data**|Data Size - 12|Image data|
<sub><sup>Table 2.3</sup></sub>