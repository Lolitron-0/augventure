<template>
  <div>
    <profile-navbar class="profileNavbar"></profile-navbar>
  </div>
</template>

<script>
import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";

export default {
  components: {ProfileNavbar}

}
</script>

<style scoped>
@import "@/styles.css";

.profileNavbar {
  position: absolute;
  top: 100px;
  justify-content: center;
}
</style>