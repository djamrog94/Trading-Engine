#include "Order.h"
namespace TradingEngine::Orderbook {
	void TradingEngine::Orderbook::Order::IncreaseQuantity(uint16_t quantityDelta)
	{
		currentQuantity_ += quantityDelta;
	}

	void TradingEngine::Orderbook::Order::DecreaseQuantity(uint16_t quantityDelta)
	{
		if (quantityDelta > currentQuantity_) throw std::invalid_argument("Delta cannot be greater than current quantity!");
		currentQuantity_ -= quantityDelta;
	}

	Order::Order(OrderCore& orderBase, long price, uint16_t quantity, bool isBuySide)
		: orderBase_(orderBase), price_(price), initialQuantity_(quantity), currentQuantity_(quantity), isBuySide_(isBuySide) {}

	Order::Order(ModifyOrder& modifyOrder)
		: orderBase_(modifyOrder.getCore()), price_(modifyOrder.getPrice()), initialQuantity_(modifyOrder.getQuantity()),
		currentQuantity_(modifyOrder.getQuantity()), isBuySide_(modifyOrder.getIsBuySide()) {}
}
