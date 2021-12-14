#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>

template <typename T>
class AvlTree {

private:
    struct Node {
        T value_;
        std::shared_ptr<Node> left_;
        std::shared_ptr<Node> right_;
        int height_;

        Node(const T& value, std::shared_ptr<Node> lt = nullptr,
            std::shared_ptr<Node> rt = nullptr, int height = 0)
            : value_ { value }
            , left_ { lt }
            , right_ { rt }
            , height_ { height } {};

        Node(T&& value, std::shared_ptr<Node> lt = nullptr,
            std::shared_ptr<Node> rt = nullptr, int height = 0)
            : value_ { std::move(value) }
            , left_ { lt }
            , right_ { rt }
            , height_ { height } {};
    };

public:
    AvlTree() = default;
    AvlTree(const AvlTree& other) { root_ = clone(other.root_); };
    ~AvlTree() = default;

    const T& findMax() const { return findMax(root_); };
    const T& findMin() const { return findMin(root_); };
    const T& next(const T& value) const { return next(value, root_); };

    bool find(const T& value) const { return find(value, root_) != 0; };
    bool isEmpty() const { return !root_; };
    int getCount() const { return getCount(root_); };
    int getHeight() const { return getHeight(root_); };

    void print() const
    {
        print(root_);
        std::cout << std::endl;
    };

    void insert(const T& value) { insert(value, root_); };
    void insert(T&& value) { insert(value, root_); };
    void remove(const T& value) { remove(value, root_); };
    void empty() { root_ = nullptr; };

    AvlTree& operator=(const AvlTree& other)
    {
        if (this != &other)
            root_ = clone(other.root_);
        return *this;
    }

private:
    std::shared_ptr<Node> root_ { nullptr };

    const T& findMin(const std::shared_ptr<Node>& node) const
    {
        if (!node)
            throw std::logic_error("Empty tree");
        else if (!node->left_)
            return node->value_;
        return findMin(node->left_);
    }

    const T& findMax(const std::shared_ptr<Node>& node) const
    {
        if (!node)
            throw std::logic_error("Empty tree");
        else if (!node->right_)
            return node->value_;
        return findMax(node->right_);
    }

    const T& next(const T& value, std::shared_ptr<Node> node) const
    {
        if (!node)
            throw std::logic_error("Empty tree");

        std::shared_ptr<Node> current = nullptr;

        while (node) {
            if (value < node->value_) {
                current = node;
                node = node->left_;
            } else if (value > node->value_) {
                node = node->right_;
            } else {
                if (node->right_)
                    return findMin(node->right_);
                break;
            }
        }

        return current->value_;
    }

    std::shared_ptr<Node> find(const T& value, const std::shared_ptr<Node>& node) const
    {
        if (!node || node->value_ == value)
            return node;
        else if (node->value_ > value) {
            return find(value, node->left_);
        } else
            return find(value, node->right_);
    }

    int getCount(const std::shared_ptr<Node>& node) const
    {
        if (!node)
            return 0;
        return 1 + getCount(node->right_) + getCount(node->left_);
    }

    int getHeight(const std::shared_ptr<Node>& node) const
    {
        if (!node)
            return -1;

        return std::max(height(node->left_), height_(node->right_)) + 1;
    }

    void print(const std::shared_ptr<Node>& node) const
    {
        if (!node)
            return;

        print(node->left_);
        std::cout << node->value_ << " ";
        print(node->right_);
    }

    void insert(const T& value, std::shared_ptr<Node>& node)
    {
        if (!node)
            node = std::make_shared<Node>(value);
        else if (value < node->value_)
            insert(value, node->left_);
        else
            insert(value, node->right_);

        balance(node);
    }

    void insert(T&& value, std::shared_ptr<Node>& node)
    {
        if (!node)
            node = std::make_shared<Node>(std::move(value));
        else if (value < node->value_)
            insert(std::move(value), node->left_);
        else
            insert(std::move(value), node->right_);

        balance(node);
    }

    void remove(const T& value, std::shared_ptr<Node>& node)
    {
        if (!node)
            return;

        if (value < node->value_)
            remove(value, node->left_);
        else if (value > node->value_)
            remove(value, node->right_);
        else if (node->left_ && node->right_) {
            node->value_ = findMin(node->right_);
            remove(node->value_, node->right_);
        } else
            node = (node->left_) ? node->left_ : node->right_;

        balance(node);
    }

    void balance(std::shared_ptr<Node>& node)
    {
        if (!node)
            return;

        if (height(node->left_) - height(node->right_) > 1) {
            if (height(node->left_->left_) >= height(node->left_->right_))
                rotateWithLeftChild(node);
            else {
                rotateWithRightChild(node->left_);
                rotateWithLeftChild(node);
            }
        } else if (height(node->right_) - height(node->left_) > 1) {
            if (height(node->right_->right_) >= height(node->right_->left_))
                rotateWithRightChild(node);
            else {
                rotateWithLeftChild(node->right_);
                rotateWithRightChild(node);
            }
        }

        node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
    }

    void rotateWithLeftChild(std::shared_ptr<Node>& node)
    {
        std::shared_ptr<Node> lf = node->left_;

        node->left_ = lf->right_;
        lf->right_ = node;
        node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
        lf->height_ = std::max(height(lf->left_), node->height_) + 1;
        node = lf;
    }

    void rotateWithRightChild(std::shared_ptr<Node>& node)
    {
        std::shared_ptr<Node> rt = node->right_;

        node->right_ = rt->left_;
        rt->left_ = node;
        node->height_ = std::max(height(node->right_), height(node->left_)) + 1;
        rt->height_ = std::max(height(rt->right_), node->height_) + 1;
        node = rt;
    }

    std::shared_ptr<Node> clone(std::shared_ptr<Node> node) const
    {
        if (!node)
            return nullptr;
        return std::make_shared<Node>(node->value_, clone(node->left_), clone(node->right_));
    }

    int height(std::shared_ptr<Node> node) const
    {
        return !node ? -1 : node->height_;
    }
};

