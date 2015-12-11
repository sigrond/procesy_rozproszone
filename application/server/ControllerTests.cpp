/** \file ControllerTests.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z testami do klasy Controller.
 *
 */

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Controller.hpp"
#include "AdminServer.hpp"
#include "AgentServer.hpp"
#include "Model.hpp"
#include "Strategies.hpp"
#include <exception>
#include <iostream>

int TestStrategy::createdObjects=0;
int TestStrategy::deletedObjects=0;

BOOST_AUTO_TEST_SUITE( Controller_Tests )

	BOOST_AUTO_TEST_CASE( Controller_Test_porazki_uruchomienia_z_braku_modulow )
	{
		Controller* controller=nullptr;
		controller=new Controller();
		BOOST_REQUIRE(controller!=nullptr);
		BOOST_CHECK_THROW(controller->start(), std::exception);
	}

	BOOST_AUTO_TEST_CASE( Test_przetwarzania_komunikatow )
	{
		Controller* controller=nullptr;
		controller=new Controller();
		BOOST_REQUIRE(controller!=nullptr);
		controller->setAdminServer(new AdminServer());
        controller->setAgentServer(new AgentServer());
        Model* model=nullptr;
        model=new Model();
        BOOST_REQUIRE(model!=nullptr);
        controller->setModel(model);
        controller->setup();
		std::thread controllerThread(&Controller::start,controller);
		std::cout<<"controller->alive = "<<controller->alive<<std::endl;
		model->pushTestEvents();
		std::cout<<"controller->alive = "<<controller->alive<<std::endl;
		if(controllerThread.joinable())
		{
            controllerThread.join();
		}
		std::cout<<"controller->alive = "<<controller->alive<<std::endl;
		BOOST_CHECK(controller->alive==0);
	}

BOOST_AUTO_TEST_SUITE_END()
