# Motorola Boot logo editor

This repository is a fork of [eriktim](https://github.com/eriktim)'s [moto-bootlogo](https://github.com/eriktim/moto-bootlogo)! 

### Dependencies

The following Linux packages are requied:
* `fastboot`
* `libpng-dev`

```bash
sudo apt update
sudo apt install fastboot libpng-dev
```

## Build

```bash
make all
```

## Usage

### Extract the original bin file

>**Note:** The extraction process will only succeed if the device was rooted previously.

```bash
adb shell su -c "dd if=/dev/block/platform/msm_sdcc.1/by-name/logo of=/sdcard/logo.bin count=1 bs=634418"
adb pull /sdcard/logo.bin .
```

>**Note:** The data length on the logo partition (bs) can vary between devices.

### Modify the bin file

Choose one of the following options.

#### Extract the logos from a bin file

```bash
moto-bootlogo logo.bin
```

#### Replace the 'unlocked bootloader' logo with the original logo

```bash
moto-bootlogo -f logo.bin
```

#### Replace the bootlogo with your own logo

```bash
moto-bootlogo -i bootlogo.png logo.bin
```

### Flash the modified bin file

Make sure your device is connected in _fastboot mode_.

```bash
fastboot flash logo logo-custom.bin
```

## Notes

The source (as the original repo mentioned) is based on the script by carock's [XDA forum comment](http://forum.xda-developers.com/showpost.php?p=48891456&postcount=140).
