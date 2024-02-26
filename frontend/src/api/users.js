export default function(instance) {
    return {
        myProfile() {
            return instance.get('auth/users/me')
        },
        updateProfile(payload) {
            return instance.put('auth/users/me', payload)
        }
    }
}