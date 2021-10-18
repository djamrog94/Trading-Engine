#include "TradingEngine/Orders/Order.h"

namespace TradingEngine::Orders {
	void Order::IncreaseQuantity(uint16_t quantityDelta)
	{
		currentQuantity_ += quantityDelta;
	}

	void Order::DecreaseQuantity(uint16_t quantityDelta)
	{
		if (quantityDelta > currentQuantity_) throw std::invalid_argument("Delta cannot be greater than current quantity!");
		currentQuantity_ -= quantityDelta;
	}


	Order::Order(OrderCore& orderBase, long price, uint16_t quantity, bool isBuySide)
		: OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()), orderBase_(orderBase),
		price_(price), currentQuantity_(quantity), initialQuantity_(quantity), isBuySide_(isBuySide) {}
	
	std::ostream& operator << (std::ostream& outs, const Order& ord)
	{
		return outs << ord.orderBase_ << ": " << "Price: " << ord.price_ << ", " << "InitialQuantity: " << ord.initialQuantity_ << ", " << "CurrentQuantity: " << ord.currentQuantity_ << ", " << "IsBuySide: " << ord.isBuySide_ << std::endl;
	}
	
//	Order::Order(ModifyOrder& modifyOrder)
	//	: OrderCore(modifyOrder.getOrderId(), modifyOrder.getUsername(), modifyOrder.getSecurityId()), price_(modifyOrder.getPrice()), initialQuantity_(modifyOrder.getQuantity()),
	//	currentQuantity_(modifyOrder.getQuantity()), isBuySide_(modifyOrder.getIsBuySide()) {}
}
