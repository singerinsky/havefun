/*
 * message_filter.cpp
 *
 *  Created on: 2012-8-21
 *      Author: lixingyi
 */

#include <stdlib.h>
#include <string.h>
#include "message_filter.h"
#include <string.h>



FilterNode::FilterNode():m_char(0),m_flag(0)
{

}

FilterNode::~FilterNode()
{
    for ( std::size_t i = 0 ; i < m_nodes.size(); ++i )
    {
        if ( m_nodes[i] )
        {
            delete m_nodes[i];
        }
    }

}

FilterNode* FilterNode::find( char c )
{
    FilterNode* rc = NULL;
    std::vector<FilterNode*>::iterator it;

    for ( it = m_nodes.begin(); it != m_nodes.end(); ++it )
    {
        if ( (*it)->get_char() == c )
        {
            rc = *it;
            break;
        }
    }

    return rc;
}

void FilterNode::add(FilterNode* node )
{
    m_nodes.push_back(node);
}

MessageFilter::MessageFilter():m_root(NULL)
{

}

MessageFilter::~MessageFilter()
{
    fini() ;
}

int MessageFilter::init()
{
    m_root = new FilterNode;
    if ( m_root )
    {
        m_root->set_flag( 0 );
        m_root->set_char( 'R' );

        return 0;
    }

    return -1;
}

void MessageFilter::fini()
{
    if ( m_root )
    {
        delete m_root;
        m_root = NULL ;
    }
}

void MessageFilter::insert( FilterNode * node,const char * word, int32_t len, int32_t index )
{
    FilterNode * n = NULL;

    n = find( node, word[index] );
    if ( n == NULL )
    {
        n = new FilterNode;
        n->set_char( word[index] );
        node->add( n );
    }

    ++index;
    if ( index == len )
    {
        n->set_flag(1);
    }
    else if ( index < len )
    {
        insert( n, word, len, index );
    }

    return;
}

FilterNode * MessageFilter::find( FilterNode * node, char c )
{
    return node->find( c );
}

int MessageFilter::add_keyword(const char * word, int32_t len )
{
    len = ( len == 0 ? (int32_t)strlen(word) : len );
    if ( len <= 0 )
    {
        return -1;
    }

    insert( m_root, word, len, 0 );
    return 0;
}

int32_t MessageFilter::filter( char * message, char * out_message, int32_t len )
{
    int32_t rc = 0;
    FilterNode * node = m_root;

    int32_t i = 0, count = 0;
    bool isSamePlace = (message == out_message);

    len = ( len == 0 ? (int32_t)::strlen(message) : len );

    while ( i < len )
    {
        if ( !isSamePlace )
        {
            out_message[i] = message[i];
        }

        node = find( node, message[i] );
        if ( node == NULL )
        {
            i = i-count;
            count = 0;
            node = m_root;
        }
        else 
        {
            ++count;

            if ( node->get_flag() == 1 )
            {
                // 鍏抽敭瀛楀尮閰嶅畬姣� 鎵惧埌浜嗛渶瑕佽繃婊ょ殑瀛椾覆
                for ( int32_t index = i-count+1; index<=i; ++index )
                {
                    out_message[index] = '*';
                }

                ++rc;
                count = 0;
                node = m_root;
            }
            else if ( i == len-1 )
            {
                // 鍏抽敭瀛楄繕鍦ㄥ尮閰嶄腑, 浣嗗緟杩囨护鐨勫瓧绗︿覆宸茬粡缁撴潫浜�
                i = i-count+1;
                count = 0;
                node = m_root;
            }
        }

        ++i;
    }

    out_message[ len ] = 0;

    return rc;
}


