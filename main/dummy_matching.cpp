// A dummy PITCH Client that prints to the console.
// Copyright 2019 Christian Kauten
//

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include "limit_order_book.hpp"

using namespace LOB;


inline void spam_limit_many_market_orders(
    LimitOrderBook& book,
    int count,
    int price_mean = 60000,
    int price_variance = 1000,
    int quantity_mean = 1000,
    int quantity_variance = 10
) {
    auto generator = std::default_random_engine();
    auto price = std::normal_distribution<double>(price_mean, price_variance);
    auto quantity = std::normal_distribution<double>(quantity_mean, quantity_variance);
    for (int i = 1; i < count; i++) {
        auto price_ = static_cast<uint64_t>(price(generator));
        auto quantity_ = static_cast<uint32_t>(quantity(generator));
        // std::cout << "Limit Order: " << i << " Price: " << price_ << " Quantity: " << quantity_ << std::endl;
        book.limit(Side::Buy, i, 100, price_);
        book.market(Side::Sell, i, quantity_);
    }
}

int main() {
    int count = 5000000;
  
    // Start timing
    auto start = std::chrono::high_resolution_clock::now();
    auto book = LimitOrderBook();
    spam_limit_many_market_orders(book, count);

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Total Orders " << count << " have been submitted." << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
