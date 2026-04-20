# CSPB:2270 Final Project - Li Chow Trees

## Overview

Li Chao Trees are a data structure that efficiently manages a collection of linear functions of the form y = mx + k to determine which one “wins” for any given value of x. Typically, “winning” means minimizing or maximizing the output of a function. Each node stores the dominant function at the midpoint of a specific range and allows us to find the optimal result in O(log n) time.

## Background and Motivation

I have several years of experience building decentralized exchange infrastructure, known as a DEX, on Ethereum and other EVM blockchains. These exchanges create markets where one asset can be traded for another at a rate defined by the logic of the DEX. Most chains have many competeing DEXes and, as a result, there are multiple markets for the exact same asset pair that a user could use for their trade.

Rather than pick a specific DEX for a trade, many users will use a product called an aggregator. Aggregators index all of the available markets for a specific asset pair and, whenever a user asks for a quote, returns a quote from the DEX that gives the user the best price for their trade. In this context, "best" generally means maximizing the output amount given a defined input amount. For example, when a user wants to sell N amount of asset X for as much of asset Y as possible, the aggregator is calculating the optimal DEX to use.

While I'm glossing over a lot of the details about how this works under the hood, this knowledge prompted me to serach for a data structure that would give O(log n) time complexity to determine the optimal solution for a given input value. This led me to the data structure known as Li Chao trees.

## Example

Consider a more relatable example: would it be less expensive to fill my car with gasoline at the gas station nearest to my house or to dirve k miles to fill my car at the gas station in the next town over that has cheaper prices?

This question depends on several factors. First, what are the prices at the various gas stations? Second, how much gasoline do you need to buy? Third, how far away is each gas stations from your house and how much will it cost me to get there? The answers to these questions will determine the optimal answer to our original question - which gas station is cheapest for me to fill up at?

Mathematically, this question can be represented as a linear equation of the form y = mx + k where:

+ y = the cost to fill your car
+ m = the price per gallon at the gas station
+ x = the number of gallons purchased
+ k = the cost to get to the gas station

To answer this question using a Li Chao Tree, you would construct a tree where the dominant function minimizes the output amount.

## Data Structure

The data structure of a Li Chao Tree is similar to a Binary Search Tree (BST) with some key differences. First, the nodes in a Li Chao tree contain additional data compared to a normal BST. Second, nodes cannot simply be deleted from a Li Chao tree and instead must be rebuilt, which has the downside of O(n) time compelxity for the remove operation. 

A Node stores three unique pieces of information in addition to its left and right children. Rather than store a static value as in a BST, the Node stores a pointer to a Line (discusses below). Additionally, the Node must store minimum and maximum range values. The Line stored in the Node is the winner at the midpoint of this range. For example, if the range is 0 - 100, the Line wins when x = 50.

A Line is defined as a linear function of the form y = mx + k. The Line class stores static values for both m and k and contains a public member function *evaluate(int x)* that will calculate y for a given x value. This is used to compare different linear functions for given x values.

## API Reference

```
LiChowTree::insert()
```
Insert adds a Line to the Li Chao tree, creating a new Node in the tree as needed. Effectively, what this function does, is to evaluate a new Line against a Node's existing Line. The winning Line stays with that node. The losing Line is pushed down a level (either left or right) and the process is repeated recursively. The base case occurs when a new Node must be created for the Line. This operation is O(log n) time complexity.

```
LiChowTree::remove()
```
Remove deletes a Line from the Li Chao tree. Any given line can exist at multiple nodes within the Li Chao Tree, so we must traverse the entire tree in order to remove a Line entirely. However, unlike a BST, there is no good way to remove a Line in O(log n) time complexity. With a Li Chao tree, the entire tree must be rebuilt which is O(n) time complexity. While this operation is significantly more expensive to run, it preserves O(log n) time complexity for operations like *insert* and *query*.

```
LiChowTree::query()
```
Query searches for the best Line in the Li Chao tree for a given *x* value. It searches for a path from the root of the tree to a leaf that corresponds to the give *x* value. It then evaluates each Line in this path to determine which Line ultimately wins for the given input value. This operations is O(log n) time complexity.

## Interesting Properties

One of the primary insights of a Li Chao Tree is that when comparing two linear functions, at most they will only intersect at a single point. Seems straightforward, but it is core to how Li Chao Trees work. Once we know that a specific function is “better” than another at a specific point, we also know that it is exclusively better than the other function either to the left of that point or to the right of that point.

Consider a simple example where we have two linear functions that take values for x between 0 and 100. If function A wins when x = 50, function B will either intersect function A to the left of 50 or to the right of 50. Let's say we know the intersection point is greater than 50. This means that function B would win over function A for some set of values between 50 and 100. So, if we are evaluating which function wins when x = 30, we can know for certain that it is function A without ever having to evaluate function B for x = 30. 

This is how we achieve O(log n) time complexity!

## Instructions

I have created a demo that can be run in your terminal. After cloning the repository, run the following commands in your terminal.

```
cd build
cmake ..
make && ./final-project
```

The program load 25 values from a *lines.txt* file, creates a Line instance for each one, and inserts them into the Li Chao Tree. It then prompts the user to enter a number value between a global min a max. Once entered, it queries the Li Chao tree for the winning line and displays this to the user. Then, it removes the winning line from the tree and runs the query again, effectively giving the user the second place line.

For a visual representation of each line, I highly recommend using desmos.com.