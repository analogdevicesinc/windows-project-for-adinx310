

try:
    import requests
except ImportError:
    import subprocess
    import sys
    print("🔍 'requests' module not found. Installing it now...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "requests"])
    import requests  # Retry import after installation
import subprocess
import os
import zipfile
import shutil


def clone_git_repo(git_url, destination_folder=None):
    try:
        print(f"Cloning repository from {git_url}...")

        if destination_folder:
            destination_folder = os.path.normpath(destination_folder)
            cmd = ["git", "clone", git_url, destination_folder]
        else:
            cmd = ["git", "clone", git_url]

        subprocess.check_call(cmd)
        print(f"Repository cloned to: {destination_folder or 'default location'}")

        base_path = destination_folder or git_url.rstrip("/").split("/")[-1].replace(".git", "")
        lib_path = os.path.join(base_path, "lib")
        adinx_path = os.path.join(base_path, "adinx310-driver")

        # Create required folders
        os.makedirs(lib_path, exist_ok=True)
        os.makedirs(adinx_path, exist_ok=True)

        winpcap_path = os.path.join(lib_path, "winpcap")
        os.makedirs(winpcap_path, exist_ok=True)
        print(f"Created 'winpcap' folder at: {winpcap_path}")
        download_and_extract_winpcap(lib_path)

        # Download and extract ZIP file
        zip_url = "https://ftdichip.com/wp-content/uploads/2024/11/LibFT4222-v1.4.7.zip"
        zip_local_path = os.path.join(base_path, "LibFT4222-v1.4.7.zip")

        print(f"Downloading ZIP from {zip_url}...")
        download_file(zip_url, zip_local_path)

        print("Extracting ZIP file and copying 'imports' content into lib folder...")
        extract_and_copy_imports(zip_local_path, base_path, lib_path)

        # After that, copy dll contents from lib/ftd2xx/dll to lib/ftd2xx
        copy_dll_to_ftd2xx(lib_path)
        copy_dll_to_project_root(base_path)

    except subprocess.CalledProcessError:
        print("Git clone failed. Check the repo URL or destination folder.")
    except FileNotFoundError:
        print("Git is not installed or not found in system PATH.")
    except Exception as e:
        print(f"Unexpected error: {e}")

def download_file(url, destination):
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                      "AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/114.0.0.0 Safari/537.36"
    }
    response = requests.get(url, headers=headers, stream=True)
    response.raise_for_status()

    with open(destination, 'wb') as f:
        for chunk in response.iter_content(chunk_size=8192):
            f.write(chunk)

def extract_and_copy_imports(zip_path, extract_to_path, lib_folder):
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(extract_to_path)
    print(f"Extracted ZIP to {extract_to_path}")

    imports_folder = os.path.join(extract_to_path, "imports")

    if os.path.exists(imports_folder):
        print(f"Copying contents from '{imports_folder}' to '{lib_folder}'...")
        for item in os.listdir(imports_folder):
            s = os.path.join(imports_folder, item)
            d = os.path.join(lib_folder, item)
            if os.path.isdir(s):
                shutil.copytree(s, d, dirs_exist_ok=True)
            else:
                shutil.copy2(s, d)
        print("Contents copied successfully.")
    else:
        print(f"'imports' folder not found at: {imports_folder}")

def copy_dll_to_ftd2xx(lib_folder):
    ftd2xx_folder = os.path.join(lib_folder, "ftd2xx")
    dll_folder = os.path.join(ftd2xx_folder, "dll")

    if not os.path.exists(dll_folder):
        print(f" DLL folder not found at: {dll_folder}")
        return

    print(f"Copying all contents from '{dll_folder}' to '{ftd2xx_folder}'...")

    items_copied = 0
    for item in os.listdir(dll_folder):
        src_path = os.path.join(dll_folder, item)
        dest_path = os.path.join(ftd2xx_folder, item)

        try:
            # If destination exists, remove it first (file or folder)
            if os.path.exists(dest_path):
                if os.path.isfile(dest_path) or os.path.islink(dest_path):
                    os.remove(dest_path)
                elif os.path.isdir(dest_path):
                    shutil.rmtree(dest_path)

            # Copy file or folder
            if os.path.isfile(src_path):
                shutil.copy2(src_path, dest_path)
            elif os.path.isdir(src_path):
                shutil.copytree(src_path, dest_path)
            items_copied += 1
            print(f"Copied: {item}")

        except Exception as e:
            print(f"Failed to copy '{item}': {e}")

    if items_copied == 0:
        print("⚠️ No files or directories copied from DLL folder.")
    else:
        print(f" {items_copied} item(s) copied successfully from DLL folder.")

def copy_dll_to_project_root(base_path):
    source_dll = os.path.join(base_path, "lib", "LibFT4222", "dll", "amd64", "LibFT4222-64.dll")
    dest_dll = os.path.join(base_path, "LibFT4222-64.dll")

    if not os.path.isfile(source_dll):
        print(f" DLL file not found at: {source_dll}")
        return

    try:
        shutil.copy2(source_dll, dest_dll)
        print(f" '{os.path.basename(source_dll)}' copied to project root: {dest_dll}")
    except Exception as e:
        print(f" Failed to copy DLL to project root: {e}")

def download_and_extract_winpcap(lib_folder):
    winpcap_folder = os.path.join(lib_folder, "winpcap")
    zip_url = "https://www.winpcap.org/install/bin/WpdPack_4_1_2.zip"
    zip_local_path = os.path.join(winpcap_folder, "WpdPack_4_1_2.zip")

    try:
        print(f"Downloading WinPcap pack from {zip_url}...")
        download_file(zip_url, zip_local_path)

        print("Extracting WinPcap contents...")
        with zipfile.ZipFile(zip_local_path, 'r') as zip_ref:
            for member in zip_ref.namelist():
                # Remove the top-level WpdPack/ from the path
                stripped_path = member.partition("WpdPack/")[2]
                if stripped_path:
                    dest_path = os.path.join(winpcap_folder, stripped_path)
                    if member.endswith('/'):
                        os.makedirs(dest_path, exist_ok=True)
                    else:
                        os.makedirs(os.path.dirname(dest_path), exist_ok=True)
                        with zip_ref.open(member) as source, open(dest_path, 'wb') as target:
                            shutil.copyfileobj(source, target)

        # Optional cleanup
        os.remove(zip_local_path)

        print(f" WinPcap extracted to: {winpcap_folder}")
    except Exception as e:
        print(f" Failed to download or extract WinPcap: {e}")


if __name__ == "__main__":
    git_repo_url = "https://github.com/analogdevicesinc/windows-project-for-adinx310"
    destination = r"C:\WindowsProject"
    clone_git_repo(git_repo_url, destination)
