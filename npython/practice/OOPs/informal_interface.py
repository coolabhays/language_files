#!/usr/bin/env python3

"""
reference: https://realpython.com/python-interface/#informal-interfaces
"""

class InformalParserInterface:
    def load_data_source(self, path: str, file_name: str) -> str:
        """load in the file for extracting text"""
        pass

    def extract_text(self, full_name: str) -> dict:
        """extract text from currently loaded file"""
        pass

class PdfParser(InformalParserInterface):
    """Extract text from a pdf"""
    def load_data_source(self, path: str, file_name: str) -> str:
        """Overrides InformalParserInterface.load_data_source()"""
        pass

    def extract_text(self, full_file_path: str) -> dict:
        """Overrides InformalParserInterface.extract_text()"""
        pass

class EmlParser(InformalParserInterface):
    """Extract text from an email"""
    def load_data_source(self, path: str, file_name: str) -> str:
        """Overrides InformalParserInterface.load_data_source()"""
        pass

    def extract_text_from_email(self, full_file_path: str) -> dict:
        """A method defined only in EmlParser
        Does not override InformalParserInterface.extract_text()"""
        pass

print(issubclass(PdfParser, InformalParserInterface))  # True
print(issubclass(EmlParser, InformalParserInterface))  # True, even though the EmlParser fails to properly define .extract_text()
# hence, this returning 'True' is a problem(violation of definition of interface)

print(PdfParser.__mro__)  # method resolution order(MRO)
print(EmlParser.__mro__)

# this approach above is not ideal for large codebases

print("\n------------------------------")
print("------------------------------\n")

# using metaclass

# by using a metaclass, you don't explicitly define the subclass. Instread the subclass must define the required methods
# if it doesn't then issubclass(EmlParserNew, UpdatedInformalParserInterface) will return false(see below)

# we'll be overriding 2 dunder methods
class ParserMeta(type):
    """A parser metaclass that will be used for parser class creation"""
    def __instancecheck__(cls, instance):
        return cls.__subclasscheck__(type(instance))

    def __subclasscheck__(cls, subclass):
        return (hasattr(subclass, 'load_data_source')
                and callable(subclass.load_data_source)
                and hasattr(subclass, 'extract_text')
                and callable(subclass.extract_text))

class UpdatedInformalParserInterface(metaclass=ParserMeta):
    """This interface is used for concrete classes to inherit from.
    There is no need to define the ParserMeta methods as any class as they are
    implicitly made available via .__subclasscheck___()"""

# concrete implementations
class PdfParserNew:
    """Extract text from a pdf"""
    def load_data_source(self, path: str, file_name: str) -> str:
        """Overrides UpdatedInformalParserInterface.load_data_source()"""
        pass

    def extract_text(self, full_file_path: str) -> dict:
        """Overrides UpdatedInformalParserInterface.extract_text()"""
        pass

class EmlParserNew:
    """Extract text from an email"""
    def load_data_source(self, path: str, file_name: str) -> str:
        """Overrides UpdatedInformalParserInterface.load_data_source()"""
        pass

    def extract_text_from_email(self, full_file_path: str) -> dict:
        """A method defined only in EmlParser.
        Does not override UpdatedInformalParserInterface.extract_text()"""
        pass

print(issubclass(PdfParserNew, UpdatedInformalParserInterface))  # True
print(issubclass(EmlParserNew, UpdatedInformalParserInterface))  # False

print(PdfParserNew.__mro__)
print(EmlParserNew.__mro__)
# though UpdatedInformalParserInterface is superclass of PdfParserNew, but it doesn't
# appear in MRO. This unusual behavior is caused by the fact that UpdatedInformalParserInterface
# is virtual base class of PdfParserNew


print("\n------------------------------")
print("------------------------------\n")

# Using Virtual Base Classes

class PersonMeta(type):
    """A person metaclasss"""
    def __instancecheck__(cls, instance):
        return cls.__subclasscheck__(type(instance))

    def __subclasscheck__(cls, subclass):
        return (hasattr(subclass, "name")
                and callable(subclass.name)
                and hasattr(subclass, "age")
                and callable(subclass.age))

class PersonSuper:
    """A person superclass"""
    def name(self) -> str:
        pass

    def age(self) -> int:
        pass

class Person(metaclass=PersonMeta):
    """Person interface built from PersonMeta metaclass"""

# Here, you have the setup for creating virtual base classes:
# 1. The metaclass PersonMeta
# 2. The base class PersonSuper
# 3. The python interface Person

# Employee class inherits PersonSuper
# Inheriting Subclass
class Employee(PersonSuper):
    """Inherits from PersonSuper
    PersonSuper will appear in Employee.__mro__"""
    pass

class Friend:
    """Built implicitly from Person
    Friend is a virtual subclass of Person since
    both required methods exist.
    Person not in Friend.__mro__"""
    def name(self):
        pass

    def age(self):
        pass
# due to implementations of .name() and .age(), Person becomes a virtual base class
# of Friend

print(issubclass(Friend, Person))  # True
print(issubclass(Employee, Person))  # True
print(issubclass(Employee, PersonSuper))  # True
print(isinstance(Friend, Person))  # False
print(isinstance(Employee, Person))  # False
print(isinstance(Employee, PersonSuper))  # False
