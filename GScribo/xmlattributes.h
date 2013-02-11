#ifndef XMLATTRIBUTES_H
#define XMLATTRIBUTES_H

#include <QDomNamedNodeMap>

class XmlAttributes
{
    public:
        explicit XmlAttributes();
        explicit XmlAttributes(const QDomNamedNodeMap& node);

        void load(const QDomNamedNodeMap& node);

        inline QStringList names() const;
        inline QStringList values() const;

    private:
        QStringList names_;
        QStringList values_;
};

inline QStringList XmlAttributes::names() const
{ return names_; }

inline QStringList XmlAttributes::values() const
{ return values_; }

#endif // XMLATTRIBUTES_H
