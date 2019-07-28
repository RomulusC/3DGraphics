#include "LayerStack.h"

namespace Engine
{
    LayerStack::LayerStack()
    {
        //initiate the iterator at the beginning of Layer vector
        m_LayerInsert = m_Layers.begin();
    }
    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
        {
            delete layer;
        }
        /*
            Object lifetime is that popping a layer doesn't delete the layer.
            all layers get deleted once the destructor is called, which is currently 
            when the application closes. 
        */
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
    }
    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), /*m_LayerInsert */ m_Layers.end(), layer);
        if(it!= m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerInsert--;
        }
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);

    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        
        auto it = std::find(m_LayerInsert, m_Layers.end(), overlay);
        if(it!= m_Layers.end())
            m_Layers.erase(it);        
    }
}