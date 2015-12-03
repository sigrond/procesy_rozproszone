/** \file BlockingQueueTests.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z testami do klasy BlockingQueue.
 *
 */

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "BlockingQueue.hpp"

BOOST_AUTO_TEST_SUITE( BlockingQueue_Test )

BOOST_AUTO_TEST_CASE( BQ1 )
{
    BlockingQueue<int> q;
    q.push_back(1);
    int n=0;
    n=q.pop_front();
    BOOST_CHECK( n==1 );
}

BOOST_AUTO_TEST_SUITE_END()
