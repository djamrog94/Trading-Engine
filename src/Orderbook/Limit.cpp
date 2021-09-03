#include "TradingEngine/Orderbook/Limit.h"

namespace TradingEngine::Orderbook {
	Limit::Limit(long price) : price_(price)
	{
		head_ = NULL;
		tail_ = NULL;
	}

	long Limit::getPrice()
	{
		return price_;
	}
	OrderbookEntry Limit::getHead()
	{
		return *head_;
	}
	OrderbookEntry Limit::getTail()
	{
		return *tail_;
	}
	void Limit::setPrice(long price)
	{
		price_ = price;
	}

	//void Limit::setHead(OrderbookEntry& head)
	//{
	//	head_ = &head;
	//}
	//void Limit::setTail(OrderbookEntry& tail)
	//{
	//	tail_ = &tail;
	//}
}
