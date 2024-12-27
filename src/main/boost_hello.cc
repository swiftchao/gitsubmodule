#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

int test_date_time() {
    // 获取当前时间
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();

    // 输出时间
    std::cout << now << std::endl;

    return 0;
}

int test_date_time_2() {
    // 获取当前日期
    /*
    boost::gregorian::date today = boost::gregorian::from_string(boost::gregorian::to_iso_string(boost::gregorian::day_clause::local_day()));
    std::cout << "当前日期: " << today << std::endl;
    */

    // 进行简单日期运算，计算两个日期的间隔天数
    boost::gregorian::date start_date(2024, 1, 1);
    boost::gregorian::date end_date(2024, 12, 31);
    boost::gregorian::date_duration diff = end_date - start_date;
    std::cout << "从 " << start_date << " 到 " << end_date << " 的天数间隔: " << diff.days() << " 天" << std::endl;

    return 0;

}

int main(void) {
    test_date_time();
    test_date_time_2();
    return 0;
}


