/**
 *  @file   ModifyOrder.cpp
 *  @brief  Modify order object
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#include "TradingEngine/Orders/ModifyOrder.h"
#include "TradingEngine/Orders/OrderCore.h"

namespace TradingEngine::Orders {
	/*! \brief Returns price of ModifyOrder object.
	*/
	long ModifyOrder::getPrice()
	{
		return price_;
	}
	/*! \brief Returns quanitity of ModifyOrder object.
	*/
	uint16_t ModifyOrder::getQuantity()
	{
		return modifyQuantity_;
	}
	/*! \brief Returns if ModifyOrder is buy side or not.
	*/
	bool ModifyOrder::getIsBuySide()
	{
		return isBuySide_;
	}

	/*! \brief Returns a CancelOrder object based on ModifyOrder object.
	*/
	CancelOrder ModifyOrder::toCancelOrder()
	{
		OrderCore newOrderCore = OrderCore(getOrderId(), getUsername(), getSecurityId());
		return CancelOrder(newOrderCore);
	}

	/*! \brief Returns a Order object based on ModifyOrder object. 
	*/
	Order ModifyOrder::toNewOrder()
	{
		OrderCore newOrderCore = OrderCore(getOrderId(), getUsername(), getSecurityId());
		return Order(newOrderCore, price_, modifyQuantity_, isBuySide_);
	}
	/*! \brief Constructor for ModifyOrder.
	*/
	ModifyOrder::ModifyOrder(OrderCore& orderBase, long price, uint16_t modifyQuantity, bool isBuySide)
		: OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()),
		orderBase_(orderBase), price_(price), modifyQuantity_(modifyQuantity), isBuySide_(isBuySide) {}
	

	/*! \brief Returns reference to ostream containing string representation of ModifyOrder object.
	*/
	std::ostream& operator << (std::ostream& outs, const ModifyOrder& mo)
	{
		return outs << mo.orderBase_ << ": " << "Price: " << mo.price_ << ", " << "Quantity: "
			<< mo.modifyQuantity_ << ", " << "IsBuySide: " << mo.isBuySide_ << std::endl;
	}
}
