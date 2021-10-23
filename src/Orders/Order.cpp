/**
 *  @file   Order.cpp
 *  @brief  Order object
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#include "TradingEngine/Orders/Order.h"

namespace TradingEngine::Orders {
	/*! \brief Increases quantity of Order object.
	*/
	void Order::IncreaseQuantity(uint16_t quantityDelta)
	{
		currentQuantity_ += quantityDelta;
	}

	/*! \brief Decreases quantity of Order object.
	*/
	void Order::DecreaseQuantity(uint16_t quantityDelta)
	{
		if (quantityDelta > currentQuantity_)
			throw std::invalid_argument("Delta cannot be greater than current quantity!");
		currentQuantity_ -= quantityDelta;
	}

	/*! \brief Constructor for Order.
	*/
	Order::Order(OrderCore& orderBase, long price, uint16_t quantity, bool isBuySide)
		: OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()), orderBase_(orderBase),
		price_(price), currentQuantity_(quantity), initialQuantity_(quantity), isBuySide_(isBuySide) {}
	
	/*! \brief Returns reference to ostream containing string representation of Order object.
	*/
	std::ostream& operator << (std::ostream& outs, const Order& ord)
	{
		return outs << ord.orderBase_ << ": " << "Price: " << ord.price_ << ", " 
			<< "InitialQuantity: " << ord.initialQuantity_ << ", " << "CurrentQuantity: "
			<< ord.currentQuantity_ << ", " << "IsBuySide: " << ord.isBuySide_ << std::endl;
	}
}
