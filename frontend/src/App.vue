<template>

  <navbar v-if="showNavbar"></navbar>
  <div id="app">
    <router-view @updateCurrentPage="updateCurrentPage"/>
  </div>

</template>

<script>
import Navbar from "@/components/Navbar.vue";
export default {
  components: {Navbar},
  data() {
    return {
      currentPageMeta: { state: 'main' }
    };
  },
  computed: {
    showNavbar() {
      return this.currentPageMeta.state === 'main';
    },
    updateCurrentPage() {
      this.currentPageMeta.state = this.$route.meta.state || 'empty';
    }
  },
}
</script>

<style>

* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: 'Poppins', sans-serif;
}

ul, li {
  list-style: none;
}
</style>

