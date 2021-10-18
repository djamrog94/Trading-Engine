#include "TradingEngine/Orders/ModifyOrder.h"
#include "TradingEngine/Orders/OrderCore.h"

namespace TradingEngine::Orders {
	long ModifyOrder::getPrice()
	{
		return price_;
	}
	uint16_t ModifyOrder::getQuantity()
	{
		return modifyQuantity_;
	}
	bool ModifyOrder::getIsBuySide()
	{
		return isBuySide_;
	}

	CancelOrder ModifyOrder::toCancelOrder()
	{
		OrderCore newOrderCore = OrderCore(getOrderId(), getUsername(), getSecurityId());
		return CancelOrder(newOrderCore);
	}

	Order ModifyOrder::toNewOrder()
	{
		OrderCore newOrderCore = OrderCore(getOrderId(), getUsername(), getSecurityId());
		return Order(newOrderCore, price_, modifyQuantity_, isBuySide_);
	}

	ModifyOrder::ModifyOrder(OrderCore& orderBase, long price, uint16_t modifyQuantity, bool isBuySide)
		: OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()), orderBase_(orderBase), price_(price), modifyQuantity_(modifyQuantity), isBuySide_(isBuySide) {}
	
	std::ostream& operator << (std::ostream& outs, const ModifyOrder& mo)
	{
		return outs << mo.orderBase_ << ": " << "Price: " << mo.price_ << ", " << "Quantity: " << mo.modifyQuantity_ << ", " << "IsBuySide: " << mo.isBuySide_ << std::endl;
	}
}
