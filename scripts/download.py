import os
import wget
import tarfile
import shutil

# 定义目标 URL 和本地保存路径
url = "http://konect.cc/files/download.tsv.lastfm_band.tar.bz2"
download_dir = "downloads"  # 临时下载目录,用来保存压缩文件
dataset_dir = "datasets"    # 解压后的目标目录

# 创建目录
os.makedirs(download_dir, exist_ok=True)
os.makedirs(dataset_dir, exist_ok=True)

# 下载文件
print("开始下载文件...")
downloaded_file = wget.download(url, out=download_dir)
print(f"\n文件下载完成: {downloaded_file}")

# 解压文件
print("正在解压文件...")
if tarfile.is_tarfile(downloaded_file):
    with tarfile.open(downloaded_file, "r:bz2") as tar:
        tar.extractall(path=download_dir)
        print(f"文件解压完成，内容解压到: {download_dir}")
else:
    print("文件格式不正确，无法解压！")
    exit(1)

# 获取解压后的文件名
extracted_files = os.listdir(download_dir)
for file_name in extracted_files:
    file_path = os.path.join(download_dir, file_name)
    if os.path.isfile(file_path) and file_path != downloaded_file:
        shutil.move(file_path, os.path.join(dataset_dir, file_name))

# 删除压缩包
print("删除压缩包...")
os.remove(downloaded_file)
print("压缩包已删除。")

# 输出结果
print(f"文件已移动到 {dataset_dir} 目录，脚本运行完成！")