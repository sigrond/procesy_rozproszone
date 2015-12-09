/** \file ControllerTests.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z testami do klasy Controller.
 *
 */

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Controller.hpp"
#include <exception>

BOOST_AUTO_TEST_SUITE( Controller_Tests )

	BOOST_AUTO_TEST_CASE( Controller_Test_porazki_uruchomienia_z_braku_modulow )
	{
		Controller* controller=nullptr;
		controller=new Controller();
		BOOST_REQUIRE(controller!=nullptr);
		BOOST_CHECK_THROW(controller->start(), std::exception);
	}

BOOST_AUTO_TEST_SUITE_END()
