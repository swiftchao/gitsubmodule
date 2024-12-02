/*************************************************************************
    > File Name: glog_hello.cc
    > Author: chaofei
    > Mail: chaofeibest@163.com 
    > Created Time: 2024-11-29 15:56:54
 ************************************************************************/
#include <glog/logging.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

void init_glog(const char* app_name) 
{
    google::InitGoogleLogging(app_name);
}

void glog_stdout() 
{
    // 初始化glog，参数为程序名称，会在日志中体现
    //google::InitGoogleLogging(app_name);

    // 设置将日志输出到标准错误输出（stderr），方便在终端查看日志
    FLAGS_logtostderr = true;

    // 记录不同级别的日志
    LOG(INFO) << "这是一条INFO级别的日志";
    LOG(WARNING) << "这是一条WARNING级别的日志";
    LOG(ERROR) << "这是一条ERROR级别的日志";
    // LOG(FATAL) << "这是一条FATAL级别的日志";

}

int create_dir(const char* dir)
{
    struct stat st;
    if (stat(dir, &st) == -1) {
        // 文件夹不存在，尝试创建
        if (mkdir(dir, 0755) == -1) {
            std::cerr << "无法创建文件夹" << std::endl;
            return -1;
        } else {
            std::cout << "文件夹创建成功" << std::endl;
        }
    } else {
        std::cout << "文件夹已存在" << std::endl;
    }
    return 0;
}

void glog_file() 
{
    FLAGS_logtostderr = false;
    const char* log_dir = "/tmp/logs";
    FLAGS_log_dir = log_dir; 
    create_dir(log_dir);
    FLAGS_max_log_size = 10 * 1024 * 1024;  // 设置为10MB
    LOG(INFO) << "这是一条INFO级别的日志";
    LOG(WARNING) << "这是一条WARNING级别的日志";
    LOG(ERROR) << "这是一条ERROR级别的日志";
}

void glog_vlog(int argc, char* argv[])
{
    //google::InitGoogleLogging(argv[0]);
    FLAGS_v = google::int32(std::stoi(argv[1]));
    LOG(INFO) << "Hello, GOOGLE!";
    VLOG(100) << "VLOG INFO 100";
    VLOG(50) << "VLOG INFO 50";
    VLOG(10) << "VLOG INFO 10";
}

int main(int argc, char* argv[]) 
{
    init_glog(argv[0]);
    glog_stdout();
    glog_file();
    glog_vlog(argc, argv);
    return 0;
}
