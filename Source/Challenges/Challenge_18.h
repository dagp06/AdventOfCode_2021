#pragma once

#include "Common/Challenge.h"

#include <set>
#include <queue>

using namespace std;


class CChallenge_18 : public CChallenge
{
    class Node;
    class Leaf;

private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    enum class ReductionAction
    {
        Explode,
        Split
    };

    struct ReductionStep
    {
        ReductionStep(Node* _node, ReductionAction _action) : m_node(_node), m_action(_action) {}

        void Print() const;

        friend bool operator< (const ReductionStep& _lhs, const ReductionStep& _rhs)
        {
            return _lhs.m_action < _rhs.m_action;
        }

        Node* m_node;
        ReductionAction m_action;
    };

    class Node
    {
    public:
        Node(Node* _parent) : m_parent(_parent) {}
        Node(const Node& _obj) : m_parent(_obj.m_parent) {}
        virtual ~Node() {}
        virtual Node* Clone() const = 0;

        virtual void Print() const = 0;

        virtual void GatherNextReductionStep(ReductionStep*& _outReductionStep) = 0;

        virtual Leaf* FetchLeftNeighboor(Node* _source) = 0;
        virtual Leaf* FetchRightNeighboor(Node* _source) = 0;

        virtual int ComputeMagnitude() const = 0;
        int ComputeDepth() const;

        Node* GetParent() { return m_parent; }
        void SetParent(Node* _node) { m_parent = _node; }

    protected:
        Node* m_parent;
    };

    class NodeComposite : public Node
    {
    public:
        NodeComposite() : Node(nullptr), m_left(nullptr), m_right(nullptr) {}
        NodeComposite(const NodeComposite& _obj);
        NodeComposite(Node* _parent) : Node(_parent), m_left(nullptr), m_right(nullptr) {}
        virtual ~NodeComposite();
        virtual NodeComposite* Clone() const override;

        void Build(queue<char>& _numberString);
        virtual void Print() const override;

        virtual void GatherNextReductionStep(ReductionStep*& _outReductionStep) override;

        virtual Leaf* FetchLeftNeighboor(Node* _source) override;
        virtual Leaf* FetchRightNeighboor(Node* _source) override;

        virtual int ComputeMagnitude() const override;

        Node* GetLeft() { return m_left; }
        Node* GetRight() { return m_right; }
        void SetLeft(Node* _node);
        void SetRight(Node* _node);
        void ReplaceChild(Node* _nodeToReplace, Node* _newNode);

    private:
        Node* m_left;
        Node* m_right;
    };

    class Leaf : public Node
    {
    public:
        Leaf(Node* _parent) : Node(_parent), m_value(0) {}
        Leaf(const Leaf& _obj) : Node(_obj), m_value(_obj.m_value) {}
        virtual Leaf* Clone() const override;

        virtual void Print() const override;

        virtual void GatherNextReductionStep(ReductionStep*& _outReductionStep) override;

        virtual Leaf* FetchLeftNeighboor(Node* _source) override;
        virtual Leaf* FetchRightNeighboor(Node* _source) override;

        virtual int ComputeMagnitude() const override;

        const int& GetValue() const { return m_value; }
        void SetValue(int _value) { m_value = _value; }

    private:
        int m_value = 0;
    };

    class Number
    {
    public:

        Number() : m_root(new NodeComposite()) {}
        Number(const Number& _obj);
        ~Number();

        void Build(const string& _numberString);
        void Print() const;

        int ComputeMagnitude() const;
        void Reduce();
        void GatherNextReductionStep(ReductionStep*& _outReductionStep);
        void ProcessReductionStep(ReductionStep* _reductionStep);
        void ExplodeNode(Node* _node);
        void SplitNode(Node* _node);
        Number& operator+=(const Number& _rhs);

        Node* GetRoot() { return m_root; }

    private:
        NodeComposite* m_root = nullptr;
    };

    vector<Number> m_numbers;
};
