/** \file Model.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy modelu
 *
 */

#pragma once

#include "BlockingQueue.hpp"

/** \brief klasa modelu
 */
class Model
{
public:
    Model();
    void setBlockingQueue(BlockingQueue*);
private:
    BlockingQueue* blockingQueue;
};

