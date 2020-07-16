//
// Created by chorm on 2020-06-05.
//

#include <xlang++/Visit.hpp>

namespace lccc::xlang{
    Visitor::Visitor(Visitor* other):other{other}{}

    void Visitor::visitEnd() {
        if(other)
            other->visitEnd();
    }
    void Visitor::visitDiagnostic(std::string_view sv) {
        if(other)
            other->visitDiagnostic(sv);
    }

    IdentifierVisitor::IdentifierVisitor(IdentifierVisitor *other) : Visitor{other} {

    }

    void IdentifierVisitor::visitRoot() {
        if(auto* id = this->get_parent<IdentifierVisitor>();id)
            id->visitRoot();
    }

    void IdentifierVisitor::visitComponent(std::string_view name) {
        if(auto* id = this->get_parent<IdentifierVisitor>();id)
            id->visitComponent(name);
    }

    void IdentifierVisitor::visitSpecialComponent(std::string_view name) {
        if(auto* id = this->get_parent<IdentifierVisitor>();id)
            id->visitSpecialComponent(name);
    }

    AnnotationVisitor::AnnotationVisitor(AnnotationVisitor *other) : Visitor{other} {

    }

    IdentifierVisitor *AnnotationVisitor::visitIdentifier() {
        if(auto* id = this->get_parent<AnnotationVisitor>();id)
            return id->visitIdentifier();
        else
            return nullptr;
    }

    AnnotationVisitor *AnnotationVisitor::visitMeta() {
        if(auto* id = this->get_parent<AnnotationVisitor>();id)
            return id->visitMeta();
        else
            return nullptr;
    }

    void AnnotationVisitor::visitItem(std::string_view value) {
        if(auto* id = this->get_parent<AnnotationVisitor>();id)
            id->visitItem(value);
    }

    void AnnotationVisitor::visitItem(std::uint64_t value) {
        if(auto* id = this->get_parent<AnnotationVisitor>();id)
            id->visitItem(value);
    }

    AnnotatedElementVisitor::AnnotatedElementVisitor(AnnotatedElementVisitor *other) : Visitor{other} {}

    AnnotationVisitor *AnnotatedElementVisitor::visitAnnotation() {
        if(auto* id = this->get_parent<AnnotatedElementVisitor>();id)
            return id->visitAnnotation();
        else
            return nullptr;
    }

    ScopeVisitor::ScopeVisitor(ScopeVisitor *other) : AnnotatedElementVisitor{other} {

    }

    ScopeMemberVisitor *ScopeVisitor::visitScopeMember() {
        if(auto* id = this->get_parent<ScopeVisitor>();id)
            return id->visitScopeMember();
        else
            return nullptr;
    }

    ScopeMemberVisitor::ScopeMemberVisitor(ScopeMemberVisitor *other) : AnnotatedElementVisitor{other} {}

    void ScopeMemberVisitor::visitVisibility(Visibility visibility) {
        if(auto* id = this->get_parent<ScopeMemberVisitor>();id)
            id->visitVisibility(visibility);
    }

    IdentifierVisitor *ScopeMemberVisitor::visitName() {
        if(auto* id = this->get_parent<ScopeMemberVisitor>();id)
            return id->visitName();
        else
            return nullptr;
    }

    void ScopeMemberVisitor::visitStaticAssertion(const std::function<void(ExprVisitor &)>& fn, std::string_view diagnostic) {
        if(auto* member = this->get_parent<ScopeMemberVisitor>();member)
            member->visitStaticAssertion(fn,diagnostic);
    }

    TypeAliasVisitor *ScopeMemberVisitor::visitTypeAlias() {
        if(auto* id = this->get_parent<ScopeMemberVisitor>();id)
            return id->visitTypeAlias();
        else
            return nullptr;
    }

    GenericMemberVisitor *ScopeMemberVisitor::visitGenericDeclaration() {
        if(auto* id = this->get_parent<ScopeMemberVisitor>();id)
            return id->visitGenericDeclaration();
        else
            return nullptr;
    }


    GenericDeclarationVisitor::GenericDeclarationVisitor(GenericDeclarationVisitor *parent) : Visitor{parent} {}

    GenericParameterVisitor *GenericDeclarationVisitor::visitGenericParameter() {
        if(auto* id = this->get_parent<GenericDeclarationVisitor>();id)
            return id->visitGenericParameter();
        else
            return nullptr;
    }

    GenericMemberVisitor::GenericMemberVisitor(GenericMemberVisitor *parent) : GenericDeclarationVisitor(parent) {}

    ScopeMemberVisitor *GenericMemberVisitor::visit() {
        if(auto* id = this->get_parent<GenericMemberVisitor>();id)
            return id->visit();
        else
            return nullptr;
    }

    GenericParameterVisitor::GenericParameterVisitor(GenericParameterVisitor *parent) : AnnotatedElementVisitor(parent) {}

    TypeGenericParameterVisitor *GenericParameterVisitor::visitTypeParameter() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitTypeParameter();
        else
            return nullptr;
    }

    ConstGenericParameterVisitor *GenericParameterVisitor::visitConstParameter() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitConstParameter();
        else
            return nullptr;
    }

    BoundGenericParameterVisitor *GenericParameterVisitor::visitBoundParameter() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitBoundParameter();
        else
            return nullptr;
    }

    GenericDeclarationVisitor *GenericParameterVisitor::visitGenericType() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitGenericType();
        else
            return nullptr;
    }

    void GenericParameterVisitor::visitParameterPack() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            id->visitParameterPack();
    }

    IdentifierVisitor *GenericParameterVisitor::visitName() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitName();
        else
            return nullptr;
    }

    TypeVisitor *GenericParameterVisitor::visitDefaultType() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitDefaultType();
        else
            return nullptr;
    }

    ExprVisitor *GenericParameterVisitor::visitDefaultValue() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitDefaultValue();
        else
            return nullptr;
    }

    GenericItemVisitor *GenericParameterVisitor::visitDefaultGenericType() {
        if(auto* id = this->get_parent<GenericParameterVisitor>();id)
            return id->visitDefaultGenericType();
        else
            return nullptr;
    }


    TypeVisitor::TypeVisitor(TypeVisitor *parent) : AnnotatedElementVisitor{parent} {}

    ScalarTypeVisitor *TypeVisitor::visitScalarType() {
        if(auto* id = this->get_parent<TypeVisitor>();id)
            return id->visitScalarType();
        else
            return nullptr;
    }

    PointerTypeVisitor *TypeVisitor::visitPointerType() {
        if(auto* id = this->get_parent<TypeVisitor>();id)
            return id->visitPointerType();
        else
            return nullptr;
    }

    IdentifierVisitor *TypeVisitor::visitNamedType() {
        if(auto* id = this->get_parent<TypeVisitor>();id)
            return id->visitNamedType();
        else
            return nullptr;
    }

    GenericInstantiationVisitor *TypeVisitor::visitGenericType() {
        if(auto* id = this->get_parent<TypeVisitor>();id)
            return id->visitGenericType();
        else
            return nullptr;
    }

    void TypeVisitor::visitGenericParameter(uint32_t pnum) {
        if(auto* id = this->get_parent<TypeVisitor>();id)
            id->visitGenericParameter(pnum);
    }

    ValueVisitor *TypeVisitor::visitAlignedAs() {
        if(auto* id = this->get_parent<TypeVisitor>();id)
            return id->visitAlignedAs();
        else
            return nullptr;
    }

    GenericInstantiationVisitor::GenericInstantiationVisitor(GenericInstantiationVisitor *visitor) : Visitor(visitor) {}

    GenericItemVisitor *GenericInstantiationVisitor::visitGenericItem() {
        if(auto* id = this->get_parent<GenericInstantiationVisitor>();id)
            return id->visitGenericItem();
        else
            return nullptr;
    }

    TypeVisitor *GenericInstantiationVisitor::visitTypeParameter() {
        if(auto* id = this->get_parent<GenericInstantiationVisitor>();id)
            return id->visitTypeParameter();
        else
            return nullptr;
    }

    GenericItemVisitor *GenericInstantiationVisitor::visitGenericParameter() {
        if(auto* id = this->get_parent<GenericInstantiationVisitor>();id)
            return id->visitGenericParameter();
        else
            return nullptr;
    }

    ValueVisitor *GenericInstantiationVisitor::visitConstParameter() {
        if(auto* id = this->get_parent<GenericInstantiationVisitor>();id)
            return id->visitConstParameter();
        else
            return nullptr;
    }

    BoundVisitor *GenericInstantiationVisitor::visitBoundParameter() {
        if(auto* id = this->get_parent<GenericInstantiationVisitor>();id)
            return id->visitBoundParameter();
        else
            return nullptr;
    }

    PointerTypeVisitor::PointerTypeVisitor(PointerTypeVisitor *parent) : Visitor{parent} {}

    TypeVisitor *PointerTypeVisitor::visitPointeeType() {
        if(auto* id = this->get_parent<PointerTypeVisitor>();id)
            return id->visitPointeeType();
        else
            return nullptr;
    }

    void PointerTypeVisitor::visitAliasingRule(PointerAliasingRule aliasingRule) {
        if(auto* id = this->get_parent<PointerTypeVisitor>();id)
            visitAliasingRule(aliasingRule);
    }

    ValueVisitor *PointerTypeVisitor::visitValidRange(ValidRangeType validRange) {
        if(auto* id = this->get_parent<PointerTypeVisitor>();id)
            return id->visitValidRange(validRange);
        else
            return nullptr;
    }

    ValueVisitor *PointerTypeVisitor::visitAligned() {
        if(auto* id = this->get_parent<PointerTypeVisitor>();id)
            return id->visitAligned();
        else
            return nullptr;
    }

    BoundVisitor *PointerTypeVisitor::visitRequiredBounds() {
        if(auto* id = this->get_parent<PointerTypeVisitor>();id)
            return id->visitRequiredBounds();
        else
            return nullptr;
    }

    ScalarTypeVisitor::ScalarTypeVisitor(ScalarTypeVisitor *parent) : Visitor{parent} {}

    IntegerTypeVisitor *ScalarTypeVisitor::visitIntegerType() {
        if(auto* id = this->get_parent<ScalarTypeVisitor>();id)
            return id->visitIntegerType();
        else
            return nullptr;
    }

    FloatingTypeVisitor *ScalarTypeVisitor::visitFloatingPointType() {
        if(auto* id = this->get_parent<ScalarTypeVisitor>();id)
            return id->visitFloatingPointType();
        else
            return nullptr;
    }

    void ScalarTypeVisitor::visitBitSize(uint16_t bits) {
        if(auto* id = this->get_parent<ScalarTypeVisitor>();id)
            id->visitBitSize(bits);
    }

    void ScalarTypeVisitor::visitVectorSize(uint16_t vector) {
        if(auto* id = this->get_parent<ScalarTypeVisitor>();id)
            id->visitVectorSize(vector);
    }

    IntegerTypeVisitor::IntegerTypeVisitor(ScalarTypeVisitor *parent) : Visitor{parent} {}

    void IntegerTypeVisitor::visitSigned() {
        if(auto* id = this->get_parent<IntegerTypeVisitor>();id)
            id->visitSigned();
    }

    void IntegerTypeVisitor::visitMinimumValue(std::intmax_t val) {
        if(auto* id = this->get_parent<IntegerTypeVisitor>();id)
            id->visitMinimumValue(val);
    }
    void IntegerTypeVisitor::visitMaximumValue(std::intmax_t val) {
        if(auto* id = this->get_parent<IntegerTypeVisitor>();id)
            id->visitMaximumValue(val);
    }
}
