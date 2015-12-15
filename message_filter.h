/*
 * message_filter.h
 *
 *  Created on: 2012-8-21
 *      Author: lixingyi
 */

#ifndef MESSAGE_FILTER_H_
#define MESSAGE_FILTER_H_


#include <vector>
#include <stdint.h>


class FilterNode
{

public :

    FilterNode();
    ~FilterNode();

public :

    FilterNode* find( char c );
    void add( FilterNode* node );

    void set_char( char c ) { m_char = c ;} ;
    void set_flag( int8_t flag ) {m_flag = flag; } ;

    char get_char() const { return m_char ; } ;
    int8_t get_flag() const { return m_flag ; } ;

private :

    char m_char;   //curent char
    char m_flag ;  //keyword end flag
    std::vector<FilterNode*>   m_nodes ;
};

class MessageFilter
{
public:
    MessageFilter() ;
    ~MessageFilter() ;
public:
    int init() ;
    void fini() ;

    int add_keyword(const char* word,int size = 0 ) ;
    int filter(char * in_message, char * out_message, int32_t size = 0 );

private:
    FilterNode* find(FilterNode* node, char c );
    void insert(FilterNode* node,const char * word, int32_t len, int32_t index );

private:
    FilterNode* m_root ;

} ;

#endif /* MESSAGE_FILTER_H_ */
