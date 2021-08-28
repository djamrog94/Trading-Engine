#include "ModifyOrder.h"
#include "CancelOrder.h"

namespace TradingEngine::Orderbook {
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
	OrderCore ModifyOrder::getCore()
	{
		return orderBase_;
	}

	ModifyOrder::ModifyOrder(OrderCore& orderBase, long price, uint16_t modifyQuantity, bool isBuySide)
		: orderBase_(orderBase), price_(price), modifyQuantity_(modifyQuantity), isBuySide_(isBuySide) {}
}
