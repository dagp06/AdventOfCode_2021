#include "Challenge_18.h"
#include "../Helpers/FileHelpers.h"
#include <cassert>



////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_18::sm_inputFilePath = "Inputs/Input_Challenge_18.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_18::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_numbers.reserve(lines.size());
    for (const string& line : lines)
    {
        m_numbers.push_back(Number());
        Number& number = m_numbers.back();

        number.Build(line);
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_18::Run_FirstPart()
{
#if !defined(BENCHMARK)
    Number sum = m_numbers[0];
    cout << "  ";  sum.Print(); cout << endl;
    for (int i = 1; i < m_numbers.size(); ++i)
    {
        const Number& num = m_numbers[i];
        cout << "+ "; num.Print(); cout << endl;
        sum += num;
        cout << "= "; sum.Print(); cout << endl;
    }

    cout << "Done ! The final sum's magnitude is " << sum.ComputeMagnitude() << "." << endl;
#else
    Number sum = m_numbers[0];
    for (int i = 1; i < m_numbers.size(); ++i)
    {
        const Number& num = m_numbers[i];
        sum += num;
    }
    sum.ComputeMagnitude();
#endif

    return EErrorCode::Success;
}

EErrorCode CChallenge_18::CleanUp_FirstPart()
{
    m_numbers.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_18::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_numbers.reserve(lines.size());
    for (const string& line : lines)
    {
        m_numbers.push_back(Number());
        Number& number = m_numbers.back();

        number.Build(line);
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_18::Run_SecondPart()
{
    int largestMagnitude = 0;
    for (int i = 0; i < m_numbers.size(); ++i)
    {
        for (int j = 0; j < m_numbers.size(); ++j)
        {
            if (i == j)
                continue;
            Number sum = m_numbers[i];
            sum += m_numbers[j];
            largestMagnitude = max(largestMagnitude, sum.ComputeMagnitude());
        }
    }

#if !defined(BENCHMARK)
    cout << "Done ! The largest magnitude is " << largestMagnitude << "." << endl;
#endif

    return EErrorCode::Success;
}

EErrorCode CChallenge_18::CleanUp_SecondPart()
{
    m_numbers.clear();
    return EErrorCode::Success;
}

////////////////////////////////////////////////////////
// Node
////////////////////////////////////////////////////////
int CChallenge_18::Node::ComputeDepth() const
{
    if (m_parent)
    {
        return m_parent->ComputeDepth() + 1;
    }
    else
    {
        return 0;
    }
}

CChallenge_18::NodeComposite::NodeComposite(const NodeComposite& _obj) : Node(_obj)
{
    if (_obj.m_left != nullptr)
    {
        m_left = _obj.m_left->Clone();
        m_left->SetParent(this);
    }
    else
    {
        m_left = nullptr;
    }


    if (_obj.m_right != nullptr)
    {
        m_right = _obj.m_right->Clone();
        m_right->SetParent(this);
    }
    else
    {
        m_right = nullptr;
    }
}

CChallenge_18::NodeComposite::~NodeComposite()
{
    if (m_left != nullptr)
    {
        delete m_left;
        m_left = nullptr;
    }

    if (m_right != nullptr)
    {
        delete m_right;
        m_right = nullptr;
    }
}

CChallenge_18::NodeComposite* CChallenge_18::NodeComposite::Clone() const
{
    return new NodeComposite(*this);
}

////////////////////////////////////////////////////////
// NodeComposite
////////////////////////////////////////////////////////
void CChallenge_18::NodeComposite::Build(queue<char>& _numberString)
{
    if (_numberString.empty())
        return;

    Node* left = nullptr;
    Node* right = nullptr;

    char& currentChar = _numberString.front();
    _numberString.pop();

    if (isdigit((int)currentChar))
    {
        Leaf* newLeaf = new Leaf(this);
        newLeaf->SetValue(currentChar - '0');
        left = newLeaf;
    }
    else
    {
#ifdef _DEBUG
        assert(currentChar == '[');
#endif
        NodeComposite* newComposite = new NodeComposite(this);
        newComposite->Build(_numberString);
        left = newComposite;
    }

#ifdef _DEBUG
    assert(_numberString.front() == ',');
#endif
    _numberString.pop();
    currentChar = _numberString.front();
    _numberString.pop();

    if (isdigit((int)currentChar))
    {
        Leaf* newLeaf = new Leaf(this);
        newLeaf->SetValue(currentChar - '0');
        right = newLeaf;
    }
    else
    {
#ifdef _DEBUG
        assert(currentChar == '[');
#endif
        NodeComposite* newComposite = new NodeComposite(this);
        newComposite->Build(_numberString);
        right = newComposite;

    }

#ifdef _DEBUG
    assert(_numberString.front() == ']');
#endif
    _numberString.pop();

    SetLeft(left);
    SetRight(right);
}

void CChallenge_18::NodeComposite::Print() const
{
    cout << "[";
    if (m_left != nullptr && m_right != nullptr)
    {
        m_left->Print();
        cout << ",";
        m_right->Print();
    }
    cout << "]";
}

void CChallenge_18::NodeComposite::GatherNextReductionStep(ReductionStep*& _outReductionStep)
{
    if (_outReductionStep != nullptr && _outReductionStep->m_action == ReductionAction::Explode)
        return;

    if (ComputeDepth() >= 4)
    {
        if (_outReductionStep != nullptr)
        {
            _outReductionStep->m_node = this;
            _outReductionStep->m_action = ReductionAction::Explode;
        }
        else
        {
            _outReductionStep = new ReductionStep(this, ReductionAction::Explode);
        }
        return;
    }

    m_left->GatherNextReductionStep(_outReductionStep);
    m_right->GatherNextReductionStep(_outReductionStep);
}

CChallenge_18::Leaf* CChallenge_18::NodeComposite::FetchLeftNeighboor(Node* _source)
{
    if (_source == m_left)
    {
        if (m_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            return m_parent->FetchLeftNeighboor(this);
        }
    }
    else if (_source == m_right)
    {
        return m_left->FetchLeftNeighboor(this);
    }
    else if (_source == m_parent)
    {
        return m_right->FetchLeftNeighboor(this);
    }
}

CChallenge_18::Leaf* CChallenge_18::NodeComposite::FetchRightNeighboor(Node* _source)
{
    if (_source == m_right)
    {
        if (m_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            return m_parent->FetchRightNeighboor(this);
        }
    }
    else if (_source == m_left)
    {
        return m_right->FetchRightNeighboor(this);
    }
    else if (_source == m_parent)
    {
        return m_left->FetchRightNeighboor(this);
    }
}

int CChallenge_18::NodeComposite::ComputeMagnitude() const
{
    return 3 * m_left->ComputeMagnitude() + 2 * m_right->ComputeMagnitude();
}

void CChallenge_18::NodeComposite::SetLeft(Node* _node)
{
    m_left = _node; 
    
    if (_node != nullptr)
        _node->SetParent(this);
}

void CChallenge_18::NodeComposite::SetRight(Node* _node)
{
    m_right = _node; 
    if (_node != nullptr)
        _node->SetParent(this);
}

void CChallenge_18::NodeComposite::ReplaceChild(Node* _nodeToReplace, Node* _newNode)
{
    if (_nodeToReplace == m_left)
    {
        m_left = _newNode;
    }
    else if (_nodeToReplace == m_right)
    {
        m_right = _newNode;
    }

    _newNode->SetParent(this);
}

CChallenge_18::Leaf* CChallenge_18::Leaf::Clone() const
{
    return new Leaf(*this);
}

////////////////////////////////////////////////////////
// Leaf
////////////////////////////////////////////////////////
void CChallenge_18::Leaf::Print() const
{
    cout << m_value;
}

void CChallenge_18::Leaf::GatherNextReductionStep(ReductionStep*& _outReductionStep)
{
    if (_outReductionStep == nullptr && m_value > 9)
        _outReductionStep = new ReductionStep(this, ReductionAction::Split);
}

CChallenge_18::Leaf* CChallenge_18::Leaf::FetchLeftNeighboor(Node* _source)
{
    if (_source == this)
        return m_parent->FetchLeftNeighboor(this);

    return this;
}

CChallenge_18::Leaf* CChallenge_18::Leaf::FetchRightNeighboor(Node* _source)
{
    if (_source == this)
        return m_parent->FetchRightNeighboor(this);

    return this;
}

int CChallenge_18::Leaf::ComputeMagnitude() const
{
    return m_value;
}

CChallenge_18::Number::Number(const Number& _obj)
{
    m_root = _obj.m_root->Clone();
}

CChallenge_18::Number::~Number()
{
    if (m_root != nullptr)
    {
        delete m_root;
        m_root = nullptr;
    }
}

////////////////////////////////////////////////////////
// Number
////////////////////////////////////////////////////////
void CChallenge_18::Number::Build(const string& _numberString)
{
    queue<char> workString;
    for (const char& character : _numberString)
    {
        workString.push(character);
    }


    char& currentChar = workString.front();
    workString.pop();
#ifdef _DEBUG
        assert(currentChar == '[');
#endif
    m_root->Build(workString);
#ifdef _DEBUG
    assert(workString.empty());
#endif
}

void CChallenge_18::Number::Print() const
{
    if (m_root != nullptr)
        m_root->Print();
}

int CChallenge_18::Number::ComputeMagnitude() const
{
    return m_root->ComputeMagnitude();
}

void CChallenge_18::Number::Reduce()
{
#ifdef _DEBUG
    Print();
    cout << endl;
#endif
    do
    {
        ReductionStep* nextReductionStep = nullptr;
        GatherNextReductionStep(nextReductionStep);
        if (nextReductionStep == nullptr)
            break;

#ifdef _DEBUG
        nextReductionStep->Print();
#endif

        ProcessReductionStep(nextReductionStep);

#ifdef _DEBUG
        cout << endl; Print(); cout << endl;
#endif

    } while (true);
}

void CChallenge_18::Number::GatherNextReductionStep(ReductionStep*& _outReductionStep)
{
    m_root->GatherNextReductionStep(_outReductionStep);
}

void CChallenge_18::Number::ProcessReductionStep(ReductionStep* _reductionStep)
{
    if (_reductionStep->m_action == ReductionAction::Explode)
    {
        ExplodeNode(_reductionStep->m_node);
    }
    else
    {
        SplitNode(_reductionStep->m_node);
    }
}

void CChallenge_18::Number::ExplodeNode(Node* _node)
{
    NodeComposite* nodeToExplode = static_cast<NodeComposite*>(_node);

    Leaf* leftLeaf = static_cast<Leaf*>(nodeToExplode->GetLeft());
    Leaf* leftNeighboor = leftLeaf->FetchLeftNeighboor(leftLeaf);
    if (leftNeighboor != nullptr)
    {
        leftNeighboor->SetValue(leftNeighboor->GetValue() + leftLeaf->GetValue());
    }

    Leaf* rightLeaf = static_cast<Leaf*>(nodeToExplode->GetRight());
    Leaf* rightNeighboor = rightLeaf->FetchRightNeighboor(rightLeaf);
    if (rightNeighboor != nullptr)
    {
        rightNeighboor->SetValue(rightNeighboor->GetValue() + rightLeaf->GetValue());
    }

    Leaf* newLeaf = leftLeaf; // Re-use left leaf instead of deleting it and creating a new one
    newLeaf->SetValue(0);
    NodeComposite* parent = static_cast<NodeComposite*>(nodeToExplode->GetParent());
    parent->ReplaceChild(nodeToExplode, leftLeaf);

    nodeToExplode->SetLeft(nullptr);
    delete nodeToExplode;
}

void CChallenge_18::Number::SplitNode(Node* _node)
{
    if (_node == nullptr)
        return;

    Leaf* leafToSplit = static_cast<Leaf*>(_node);

    NodeComposite* parent = static_cast<NodeComposite*>(leafToSplit->GetParent());

    NodeComposite* newCompositeNode = new NodeComposite(parent);
    
    Leaf* newLeftLeaf = new Leaf(newCompositeNode);
    newLeftLeaf->SetValue(leafToSplit->GetValue() / 2);
    newCompositeNode->SetLeft(newLeftLeaf);

    Leaf* newRightLeaf = leafToSplit; // Re-use leaf instead of deleting it and creating a new one
    newRightLeaf->SetParent(newCompositeNode);
    newRightLeaf->SetValue(ceil(leafToSplit->GetValue() / 2.f));
    newCompositeNode->SetRight(newRightLeaf);

    parent->ReplaceChild(leafToSplit, newCompositeNode);
}

CChallenge_18::Number& CChallenge_18::Number::operator+=(const Number& _rhs)
{
    NodeComposite* newRoot = new NodeComposite();
    newRoot->SetLeft(m_root);
    newRoot->SetRight(new NodeComposite(*_rhs.m_root));
    m_root = newRoot;
    Reduce();

    return *this;
}

void CChallenge_18::ReductionStep::Print() const
{
    if (m_node == nullptr) 
        return; 
    
    cout << (m_action == ReductionAction::Explode ? "Explode " : "Split "); m_node->Print(); cout << endl;
}
