/*************************************************************************
    > File Name: src/main/rapidjson_hello.cc
    > Author: chaofei
    > Mail: chaofeibest@163.com 
    > Created Time: 2024-12-03 15:25:40
 ************************************************************************/

#include <iostream>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"

int gen_json()
{
    // 1. 创建StringBuffer用于存储生成的JSON数据
    rapidjson::StringBuffer buffer;
    // 2. 创建Writer，关联到StringBuffer
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    // 3. 开始构建JSON对象
    writer.StartObject();
    writer.Key("book");
    writer.StartObject();
    writer.Key("title");
    writer.String("The Great Gatsby");
    writer.Key("author");
    writer.String("F. Scott Fitzgerald");
    writer.Key("year");
    writer.Int(1925);
    writer.Key("tags");
    writer.StartArray();
    writer.String("classic");
    writer.String("novel");
    writer.EndArray();
    writer.EndObject();
    writer.Key("is_popular");
    writer.Bool(true);
    writer.EndObject();

    // 4. 获取生成的JSON字符串并输出
    std::cout << buffer.GetString() << std::endl;

    return 0;
}

void gen_simple_json() 
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key("book");
    writer.String("The Great Gatsby");
    writer.Key("auther");
    writer.String("F. Scott Fitzgerald");
    writer.Key("year");
    writer.Int(1925);
    writer.EndObject();

    std::cout << buffer.GetString() << std::endl;
}

void gen_json_array()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key("fruits");
    writer.StartArray();
    writer.String("apple");
    writer.String("banana");
    writer.String("cherry");
    writer.EndArray();
    writer.EndObject();

    std::cout << buffer.GetString() << std::endl;
}

void gen_nested_json_str()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key("person");
    writer.StartObject();
    writer.Key("name");
    writer.String("Alice");
    writer.Key("age");
    writer.Int(25);
    writer.Key("hobbies");
    writer.StartArray();
    writer.String("reading");
    writer.String("swimming");
    writer.EndArray();
    writer.EndObject();
    writer.EndObject();

    std::cout << buffer.GetString() << std::endl;

}

void parse_json_str()
{
    const char* jsonStr = "{\"name\":\"John\", \"age\":30, \"is_student\":true}";
    rapidjson::Document doc;
    doc.Parse(jsonStr);
    if (doc.IsObject()) {
        if (doc.HasMember("name") && doc["name"].IsString()) {
            std::cout << "Name: " << doc["name"].GetString() << std::endl;
        }
        if (doc.HasMember("age") && doc["age"].IsInt()) {
            std::cout << "Age: " << doc["age"].GetInt() << std::endl;
        }
        if (doc.HasMember("is_student") && doc["is_student"].IsBool()) {
            std::cout << "is_student: " << (doc["is_student"].GetBool()? "Yes" : "No") << std::endl;
        }
    }
}

void parse_json_str_arr()
{
    const char* jsonStr = "{\"fruits\": [\"apple\", \"banana\", \"cherry\"]}";
    rapidjson::Document doc;
    doc.Parse(jsonStr);
    if (doc.IsObject() && doc.HasMember("fruits") && doc["fruits"].IsArray()) {
        for (rapidjson::SizeType i = 0 ; i < doc["fruits"].Size(); ++i) {
            if (doc["fruits"][i].IsString()) {
                std::cout << "Fruit: " << doc["fruits"][i].GetString() << std::endl;
            }
        }
    }
}

void parse_nested_json_str()
{
    const char* jsonStr = "{\"person\":{\"name\":\"Alice\", \"age\":25, \"hobbies\":[\"reading\", \"swimming\"]}}";
    rapidjson::Document doc;
    doc.Parse(jsonStr);
    if (doc.HasMember("person") && doc["person"].IsObject()) {
        const rapidjson::Value& person = doc["person"];
        if (person.HasMember("name") && person["name"].IsString()) {
            std::cout << "Name: " << person["name"].GetString() << std::endl;
        }
        if (person.HasMember("age") && person["age"].IsInt()) {
            std::cout << "Age: " << person["age"].GetInt() << std::endl;
        }
        if (person.HasMember("hobbies") && person["hobbies"].IsArray()) {
            for (rapidjson::SizeType i = 0; i < person["hobbies"].Size(); ++i) {
                if (person["hobbies"][i].IsString()) {
                    std::cout << "Hobby: " << person["hobbies"][i].GetString() << std::endl;
                }
            }
        }
    }
}

void edit_json_str() 
{
    const char* jsonStr = "{\"name\":\"Bob\", \"age\":30}";
    rapidjson::Document doc;
    doc.Parse(jsonStr);
    if (doc.HasMember("age") && doc["age"].IsInt()) {
        doc["age"].SetInt(35);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << buffer.GetString() << std::endl;
}



int main(void)
{
    gen_json();
    gen_simple_json();
    gen_json_array();
    gen_nested_json_str();
    edit_json_str();
    parse_json_str();
    parse_json_str_arr();
    parse_nested_json_str();
    return 0;
}
