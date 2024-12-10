
# SafeBoot: Secure Boot Protection for Linux

**SafeBoot** is a security program designed to protect Linux systems from threats such as **BootKitty** and other boot-level malware by ensuring that the system's boot process remains secure. The program monitors the boot process, checks for known vulnerabilities, and attempts to mitigate potential attacks.

# Before you continue:
- this is still in **Development** which means some things arent even added **yet**
- you can but **dont have to** trust this piece of software written by me (Szymon Grajner)
- **boot-level malwares** are really destructive and this program helps you avoid getting your files destroyed/corrupted/deleted
- this program alone wont help you not get infected by progrms like bootkitty **if you haven't** applied secureboot or other security options in your BIOS

## Features

### 1. **Secure Boot Check and Alert**
   - **SafeBoot** checks whether **Secure Boot** is enabled on the system.
   - If Secure Boot is not enabled, the program will notify the user and recommend enabling it for better security protection.
   - This helps prevent unauthorized bootloaders from running, a common method used by bootkits.

### 2. **Logofail Vulnerability Prevention**
   - The program ensures that the **Logofail** vulnerability cannot be easily triggered by malicious actors.
   - It blocks unauthorized access to the **Master Boot Record (MBR)**, effectively preventing bootkits from gaining control of the system after an attack.
   - This reduces the risk of malware taking control of a system even if the disk is wiped or reformatted.

### 3. **Protection for GPT Partitions**
   - **SafeBoot** extends its protection to **GPT partitions**, ensuring that **BootKitty** or other bootkits cannot modify the boot process or partition table in a way that bypasses security.
   - It ensures that the GPT partition table is securely managed, preventing manipulation of boot records or hidden partitions that could harbor bootkits.

### 4. **Kernel-Level Monitoring**
   - **SafeBoot** functions as a **kernel module**, enabling it to monitor the early boot process.
   - It scans for any suspicious boot entries, such as those associated with BootKitty or other malware, and attempts to remove them before they can execute.

### 5. **Multi-Service Support**
   - **SafeBoot** supports multiple init systems, including **systemd**, **OpenRC**, and **runit**.
   - The program is designed to automatically create and configure service files for each init system, ensuring easy deployment across various Linux distributions.

### 6. **Automated Service Setup**
   - The program can automatically generate the necessary service files (`safeboot.service` for systemd, `safeboot` for OpenRC and runit) using the **`create-services`** script.
   - The service files are created in the `services/` directory, allowing for easy installation and activation of **SafeBoot** as a system service.

### 7. **AUR Package Support**
   - **SafeBoot** is intended to be packaged for the **AUR** (Arch User Repository), enabling easy installation on Arch-based systems.
   - The program comes with a **PKGBUILD** to simplify packaging and distribution, making it accessible to users on Arch Linux and other AUR-compatible distributions.

### 8. **Customizable with Makefile**
   - The project includes a **Makefile**, which simplifies the compilation and installation of **SafeBoot**.
   - It allows users to quickly build and install the program, as well as manage the kernel module and service files.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/SafeBoot.git
   cd SafeBoot
   ```

2. **Compile the program:**
   ```bash
   make
   ```

3. **Run the service creation script:**
   ```bash
   ./create-services
   ```

4. **Install the AUR package (optional):**
   - For Arch-based systems, the program will be available on the AUR once the PKGBUILD is created and uploaded.

## Usage

After installation, **SafeBoot** will automatically monitor the system's boot process. You can enable and start the service using your init system (e.g., systemd, OpenRC, or runit):

### Systemd:
```bash
sudo systemctl enable safeboot.service
sudo systemctl start safeboot.service
```

### OpenRC:
```bash
sudo rc-update add safeboot default
sudo service safeboot start
```

### Runit:
```bash
sudo sv start safeboot
```

**SafeBoot** will now begin monitoring your boot process and securing your system against potential threats.

## Future Improvements
- **Compatibility with other Linux distributions**.
- **Enhanced logging and alerting system**.
- **Better support for detecting more advanced bootkits and rootkits**.

## License
**SafeBoot** is licensed under the BSD-3 Clause License.

---
