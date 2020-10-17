#pragma once
#include <Flow/Arithmetics.h>
#include <LangUtils.h>
#include <Parsing/SyntaxTree.h>
#include <map>
#include <set>
#include <stdexcept>

namespace Nome::Scene
{

class CSlider : public Flow::CFloatNumber
{
public:
    CSlider(AST::ACommand* cmd, float value, float min, float max, float step, std::string animfunc);

    void SetValue(float value);

    float GetMin() const { return Min; }
    float GetMax() const { return Max; }
    float GetStep() const { return Step; }
    float GetValue() const { return GetNumber(); }
    void SetAnimMax(float x);
    void SetAnimMin(float x);
    float GetAnimMax() { return AnimMax; }
    float GetAnimMin() { return AnimMin; }
    std::string GetAnimFunc() { return AnimFunc; }
    AST::ACommand* GetASTNode() const { return Cmd; }

private:
    AST::ACommand* Cmd;
    float Min;
    float Max;
    float Step;
    float AnimMax;
    float AnimMin;
    std::string AnimFunc;
};

class ISliderObserver : public tc::FNonCopyable
{
public:
    virtual void OnSliderAdded(CSlider& slider, const std::string& name) = 0;
    virtual void OnSliderRemoving(CSlider& slider, const std::string& name) = 0;

protected:
    ~ISliderObserver() = default;
};

// Manages all the sliders
class CBankAndSet : public tc::FNonCopyable
{
public:
    ~CBankAndSet();
    void AddSlider(const std::string& name, AST::ACommand* cmd, float value, float min, float max,
                   float step, std::string animfunc);
    CSlider* GetSlider(const std::string& name);

    // An observer is typically the GUI that is responsible for displaying the sliders
    void AddObserver(ISliderObserver* observer);
    void RemoveObserver(ISliderObserver* observer) { Observers.erase(observer); }

private:
    std::map<std::string, tc::TAutoPtr<CSlider>> Sliders;
    std::set<ISliderObserver*> Observers;
};

}
