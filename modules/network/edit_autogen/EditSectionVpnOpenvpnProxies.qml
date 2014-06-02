// This file is automatically generated, please don't edit manully.
import QtQuick 2.1
import Deepin.Widgets 1.0
import "../edit"

BaseEditSection { 
    id: sectionVpnOpenvpnProxies
    virtualSection: "vs-vpn-openvpn-proxies"
    
    header.sourceComponent: EditDownArrowHeader{
        text: dsTr("VPN Proxies")
    }

    content.sourceComponent: Column { 
        EditLineComboBox {
            id: lineAliasVpnOpenvpnProxiesProxyType
            // connectionSession: sectionVpnOpenvpnProxies.connectionSession
            section: "alias-vpn-openvpn-proxies"
            key: "proxy-type"
            text: dsTr("Proxy Type")
        }
        EditLineTextInput {
            id: lineAliasVpnOpenvpnProxiesProxyServer
            // connectionSession: sectionVpnOpenvpnProxies.connectionSession
            section: "alias-vpn-openvpn-proxies"
            key: "proxy-server"
            text: dsTr("Server IP")
        }
        EditLineSpinner {
            id: lineAliasVpnOpenvpnProxiesProxyPort
            // connectionSession: sectionVpnOpenvpnProxies.connectionSession
            section: "alias-vpn-openvpn-proxies"
            key: "proxy-port"
            text: dsTr("Port")
            max: 65535
            min: 0
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnProxiesProxyRetry
            // connectionSession: sectionVpnOpenvpnProxies.connectionSession
            section: "alias-vpn-openvpn-proxies"
            key: "proxy-retry"
            text: dsTr("Retry Indefinitely When Failed")
        }
        EditLineTextInput {
            id: lineAliasVpnOpenvpnProxiesHttpProxyUsername
            // connectionSession: sectionVpnOpenvpnProxies.connectionSession
            section: "alias-vpn-openvpn-proxies"
            key: "http-proxy-username"
            text: dsTr("Username")
        }
        EditLinePasswordInput {
            id: lineAliasVpnOpenvpnProxiesHttpProxyPassword
            // connectionSession: sectionVpnOpenvpnProxies.connectionSession
            section: "alias-vpn-openvpn-proxies"
            key: "http-proxy-password"
            text: dsTr("Password")
        }
    }
}
